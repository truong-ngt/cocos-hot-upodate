var res = {
    sprBg: "res/bg.png",
    sprLogo: "res/logo.png",
    loadBar: "res/loadbar.png",
};

var g_resources = [];
for (var i in res) {
    g_resources.push(res[i]);
}

cc.game.loadMainGame = function () {
    cc.loader.loadJs(["src/jsList.js"], function () {
        cc.loader.loadJs(jsList, function () {
            MGUtils.run();
        });
    });
};

cc.game.addSearchPaths = function () {
    var searchPaths = jsb.fileUtils.getSearchPaths();
    searchPaths.splice(0, 0, jsb.fileUtils.getWritablePath() + 'remote_asset/');
    jsb.fileUtils.setSearchPaths(searchPaths);
}
