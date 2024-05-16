// Primeiro, defina a altura e a largura do elemento do canvas
var canvas = document.getElementById('lineChart');
canvas.style.width = '50%'; // por exemplo, 50% do tamanho original
canvas.style.height = '50%'; // por exemplo, 50% do tamanho original

// Em seguida, obtenha o contexto e crie o gráfico
var ctx = canvas.getContext('2d');
var lineChart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: ['criar-pasta', 'criar-arquivo', 'escrever-arquivo', 'copiar', 'deletar', 'renomear', 'mover'],
        datasets: [{
            label: 'Create A new Commands',
            data: [12, 19, 3, 5, 2,4,5],
            backgroundColor: 'rgba(0,255,0,0.1)',
            borderColor: 'rgba(0,255,0,1)',
            borderWidth: 1
        }]
    }
});
