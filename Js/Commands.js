function loadContent(page) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', page, true);
    xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.querySelector('.toolsview').style.display = "none"
            document.getElementById('contentRender').style.display = "block"
            document.getElementById('lineChart').style.display = "none"
            document.getElementById('contentRender').innerHTML = this.responseText;
        } else {
            document.querySelector('.toolsview').style.display = "block"
            document.getElementById('lineChart').style.display = "block"
            document.getElementById('contentRender').style.display = "none"
        }
    };
    xhr.send();
}