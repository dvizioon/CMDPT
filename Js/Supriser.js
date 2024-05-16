
function configSuprise(event, psE, acT) {
    psE.style.display = "none";

    var stylExternal = window.getComputedStyle(acT);
    var bottomInPx = parseFloat(stylExternal.bottom);

    var parentElement = acT.parentElement;
    var parentHeight = parentElement.offsetHeight;

    var bottomInPercent = (bottomInPx / parentHeight) * 100;
    var bottomInPercentRounded = Math.round(bottomInPercent);

    // console.log("Bottom em porcentagem (arredondado): " + bottomInPercentRounded + "%");

    function moveImageUp(acT, velocity) {
        var bottomInPercent = -50; // Valor inicial de 'bottom'
        var audio = new Audio('https://www.audiosengracados.com.br/wp-content/uploads/2024/01/Audio-Engracado-E-o-pix-www.audiosengracados.com_.br_.mp3');

        var moveUp = setInterval(function () {
            if (bottomInPercent < 0) {
                acT.style.bottom = bottomInPercent + "%";
                bottomInPercent += 5;
            } else {
                audio.play();
                clearInterval(moveUp);
                // Quando o áudio terminar, comece a mover a imagem para baixo
                audio.onended = function () {
                    bottomInPercent = 0; // Reset the bottom percentage
                    var moveDown = setInterval(function () {
                        if (bottomInPercent > -50) {
                            bottomInPercent -= 5;
                            acT.style.bottom = bottomInPercent + "%";
                        } else {
                            var modal = document.getElementById('cmdModal');
                            var span = document.getElementsByClassName("close")[0];
                            modal.style.display = "block";
                        
                            span.onclick = function () {
                                modal.style.display = "none";
                                psE.style.display = "block";
                            }

                            clearInterval(moveDown);
                        }
                    }, velocity);
                };
            }
        }, velocity);
    }

    moveImageUp(acT, 300); // Substitua 300 pela velocidade desejada



}



function suprise(e) {
    idBTN = e.id

    const styleBNT = window.getComputedStyle(e)
    if (idBTN) {
        imgHacker = document.getElementById("hackerImg")
        styleBNT.display === "block" ? configSuprise(true, e, imgHacker) : false
    }
}