/*** Automatically update js and resources*/
var SplashScene = cc.Scene.extend({
    _am: null,
    _storagePath: "",
    _updating: false,
    _updateListener: null,
    _progress: null,
    count: 0,
    sprite: null,
    ctor: function () {
        this._super();
        var self = this;
        if (cc.sys.isNative) {
            cc.game.onPassCheck = function () {
                self.unscheduleAllCallbacks();
                self.checkUpdate();
            };
        }
        var size = cc.winSize;
        const bg = new cc.Sprite(res.sprBg);
        const logo = new cc.Sprite(res.sprLogo);
        bg.scaleX = size.width / 1280;
        bg.x = size.width * 0.5;
        bg.y = size.height * 0.5;
        logo.x = size.width * 0.5;
        logo.y = size.height * 0.8;
        self.sprite = new cc.Sprite(res.loadBar);
        self.sprite.attr({
            anchorX: 0,
            x: size.width * 0.5 - self.sprite.width * 0.5,
            y: size.height * 0.2
        });
        this._progress = new cc.LabelTTF.create("", "Arial", 32);
        this._progress.x = cc.winSize.width * 0.5;
        this._progress.y = cc.winSize.height * 0.1;
        self.addChild(bg);
        self.addChild(logo);
        this.addChild(this._progress);
        self.addChild(self.sprite);
        self.schedule(() => {
            self.count += 0.01;
            self.updateProgress(self.count * 100);
            if (self.count >= 1) {
                self.loadGame();
            }
        }, 0.03);
        cc.game.onPassCheck();
    },
    checkUpdate: function () {
        if (!cc.sys.isNative) {
            this.loadGame();
            return;
        }
        if (cc.sys.isNative) {
            this._storagePath = ((jsb.fileUtils ? jsb.fileUtils.getWritablePath() : '/') + 'remote_asset/');
            // console.log("=== _storagePath: " + this._storagePath);
            const customManifest = customManifestStr('https://m.mdl99.info/Start');
            this._am = new jsb.AssetsManager(customManifest, this._storagePath, versionCompareHandle);
            this._am.retain();
            this._am.setVerifyCallback(function (path, asset) {
                // When asset is compressed, we don't need to check its md5, because zip file have been deleted.
                var compressed = asset.compressed;
                // Retrieve the correct md5 value.
                var expectedMD5 = asset.md5;
                // asset.path is relative path and path is absolute.
                var relativePath = asset.path;
                // The size of asset file, but this value could be absent.
                var size = asset.size;
                if (compressed) {
                    console.log("Verification passed : " + relativePath);
                    return true;
                }
                else {
                    console.log("Verification passed : " + relativePath + ' (' + expectedMD5 + ')');
                    return true;
                }
            });

            if (cc.sys.os === cc.sys.OS_ANDROID) {
                this._am.setMaxConcurrentTask(2);
            }
        }
        if (!this._am.getLocalManifest().isLoaded()) {
            cc.log("Fail to update assets, step skipped.");
            this.loadGame();
            return;
        }
        var listener = new jsb.EventListenerAssetsManager(
            this._am, this.checkCb.bind(this));
        cc.eventManager.addListener(listener, 1);
        this._am.checkUpdate();
    },
    checkCb: function (event) {
        //console.log('Code: ' + event.getEventCode());
        switch (event.getEventCode()) {
            case jsb.EventAssetsManager.ERROR_NO_LOCAL_MANIFEST:
                console.log("No local manifest file found, hot update skipped.");
                this.loadGame();
                break;
            case jsb.EventAssetsManager.ERROR_DOWNLOAD_MANIFEST:
                this.loadGame();
                break;
            case jsb.EventAssetsManager.ERROR_PARSE_MANIFEST:
                console.log("Fail to download manifest file, hot update skipped.");
                this.loadGame();
                break;
            case jsb.EventAssetsManager.ALREADY_UP_TO_DATE:
                this.loadMainGame();
                break;
            case jsb.EventAssetsManager.NEW_VERSION_FOUND:
                this._updating = false;
                this.hotUpdate();
                return;
            default:
                return;
        }

        this._updating = false;
    },
    hotUpdate: function () {
        if (this._am && !this._updating) {
            this._updateListener = new jsb.EventListenerAssetsManager(this._am, this.updateCb.bind(this));
            cc.eventManager.addListener(this._updateListener, 1);
            this._am.update();
            this._updating = true;
        }
        else {
            console.log("lỗi cập nhật");
        }
    },
    updateCb: function (event) {
        var needRestart = false;
        var failed = false;
        switch (event.getEventCode()) {
            case jsb.EventAssetsManager.ERROR_NO_LOCAL_MANIFEST:
                console.log('No local manifest file found, hot update skipped.');
                failed = true;
                break;
            case jsb.EventAssetsManager.UPDATE_PROGRESSION:
                // this.panel.byteProgress.progress = event.getPercent() / 100;
                // this.panel.fileProgress.progress = event.getPercentByFile() / 100;
                var percent = event.getPercentByFile();
                console.log(event.getPercentByFile().toFixed(2) + '%: ' + percent);
                this.updateProgress(percent);
                break;
            case jsb.EventAssetsManager.ERROR_DOWNLOAD_MANIFEST:
                failed = true;
                break;
            case jsb.EventAssetsManager.ERROR_PARSE_MANIFEST:
                console.log('Fail to download manifest file, hot update skipped.');
                failed = true;
                break;
            case jsb.EventAssetsManager.ALREADY_UP_TO_DATE:
                console.log('Already up to date with the latest remote version.');
                failed = true;
                break;
            case jsb.EventAssetsManager.UPDATE_FINISHED:
                console.log('Update finished. ' + event.getMessage());
                needRestart = true;
                break;
            case jsb.EventAssetsManager.UPDATE_FAILED:
                console.log("vao Update failed. " + event.getMessage());
                this._updating = false;
                this._canRetry = true;
                this.retry();
                break;
            case jsb.EventAssetsManager.ERROR_UPDATING:
                console.log('Asset update error: ' + event.getAssetId() + ',' + event.getMessage());
                break;
            case jsb.EventAssetsManager.ERROR_DECOMPRESS:
                console.log("jsb.EventAssetsManager.ERROR_DECOMPRESS" + event.getMessage());
                break;
            default:
                break;
        }

        if (failed) {
            cc.eventManager.removeListener(this._updateListener);
            this._updateListener = null;
            this._updating = false;
        }

        if (needRestart) {
            console.log("====== restart game ======");
            cc.eventManager.removeListener(this._updateListener);

            this._updateListener = null;
            // Prepend the manifest's search path
            var searchPaths = jsb.fileUtils.getSearchPaths();
            var newPaths = this._am.getLocalManifest().getSearchPaths();

            Array.prototype.unshift(searchPaths, newPaths);

            // This value will be retrieved and appended to the default search path during game startup,
            // please refer to samples/js-tests/main.js for detailed usage.
            // !!! Re-add the search paths in main.js is very important, otherwise, new scripts won't take effect.
            cc.sys.localStorage.setItem('HotUpdateSearchPaths-JS', JSON.stringify(searchPaths));
            jsb.fileUtils.setSearchPaths(searchPaths);

            cc.game.restart();
        }
    },
    retry: function () {
        if (!this._updating && this._canRetry) {
            this._canRetry = false;
            console.log('Tải lại tệp lỗi...');
            this._am.downloadFailedAssets();
        }
    },
    loadMainGame: function () {
        cc.sys.localStorage.setItem('DOWNLOAD_FIRST',1);
        cc.game.loadMainGame();
    },
    loadGame: function () {
        // cc.log('Game loaded.');
        cc.loader.loadJs(["src/app.js"], function () {
            cc.game.tsStart();
        });
    },
    updateProgress: function (pc) {
        this.sprite.scaleX = pc * 0.01;
        this._progress.string = "update: " + Math.round(pc) + "%";
    },
    onExit: function () {
        // cc.log("AssetsManager::onExit");
        if (this._am)
            this._am.release();
        this._super();
    }
});
