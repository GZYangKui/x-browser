/**
 * 初始化版权信息
 */
window.onload = function () {
    let str = "©2020-%s x-browser. All Rights Reserved. navigational.cn";
    let copyright = str.replace("%s",new Date().getFullYear());
    let element = document.getElementById("crText")
    element.innerText = copyright;
}

function search() {
    let kw = document.getElementById("kw");
    window.xBrowser.jsSearch(kw.value);
}