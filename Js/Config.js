
  function loadingEffect() {
      var percent = 0;
      var loading = setInterval(function () {
          if (percent < 100) {
              document.getElementById("loading").innerHTML = "Carregando: " + percent + "%";
              percent++;
          } else {
              percent = 0;
          }
      }, 400); 
  }

  function typingEffect(command) {
      var i = 0;
      var speed = 50; 

      var span = document.createElement('span');
      span.innerHTML += '<br>';
      document.getElementById("typing").appendChild(span);

      var typing = setInterval(function () {
          if (i < command.length) {
              span.innerHTML += command[i];
              i++;
          } else {
              clearInterval(typing);
          }
      }, speed);
  }

  // Uso das funções
loadingEffect();
typingEffect("┍┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┓");
typingEffect("┏ ─────────────────────────────────────────────────────");
typingEffect("┣ cd /caminho/para/diretorio");
typingEffect("┣ touch nome-do-arquivo");
typingEffect("┣ rm nome-do-arquivo");
typingEffect("┣ cp /caminho/para/arquivo /caminho/para/diretorio");
typingEffect("┣ mv /caminho/para/arquivo /caminho/para/diretorio");
typingEffect("┣ mkdir nome-do-diretorio");
typingEffect("┗ ─────────────────────────────────────────────────────");