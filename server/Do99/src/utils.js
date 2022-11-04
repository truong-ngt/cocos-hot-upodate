function customManifestStr(hots) {
    return JSON.stringify({
        "packageUrl": hots + '/',
        "remoteManifestUrl": hots + '/project.manifest',
        "remoteVersionUrl": hots + '/version.manifest',
        "version": "0.0.0",
        "assets": {
        },
        "searchPaths": []
    });
}

function versionCompareHandle(verA, verB) {
    console.log(verA + " -> " + verB);
    var vA = verA.split('.');
    var vB = verB.split('.');
    for (var i = 0; i < vA.length; ++i) {
        var a = parseInt(vA[i]);
        var b = parseInt(vB[i] || 0);
        if (a === b) {
            continue;
        }
        else {
            return a - b;
        }
    }
    if (vB.length > vA.length) {
        return -1;
    }
    else {
        return 0;
    }
};
