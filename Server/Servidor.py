from flask import Flask, request, jsonify
from Components.Modules.DataVw import ModulesIA
import json
import requests

app = Flask(__name__)

# Rota para receber perguntas via API
@app.route('/api/question', methods=['POST'])
def pergunta():
    # Extrair dados da solicitação POST
    pergunta = request.json.get('pergunta')

    if not pergunta:
        return jsonify({"error": "Por favor, forneça uma pergunta"}), 400

    def generate_fake_user_agents(num_agents):
        user_agents = [
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.212 Safari/537.36",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:89.0) Gecko/20100101 Firefox/89.0",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:88.0) Gecko/20100101 Firefox/88.0",
            "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36",
            "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.212 Safari/537.36",
            "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Firefox/89.0",
            "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Firefox/88.0",
            "Mozilla/5.0 (iPhone; CPU iPhone OS 14_4 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/14.0.3 Mobile/15E148 Safari/604.1",
            "Mozilla/5.0 (iPad; CPU OS 14_4 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/14.0.3 Mobile/15E148 Safari/604.1",
            "Mozilla/5.0 (Linux; Android 10; SM-G960U) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.101 Mobile Safari/537.36",
            "Mozilla/5.0 (Linux; Android 11; Pixel 4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.210 Mobile Safari/537.36",
            "Mozilla/5.0 (Linux; Android 10; LM-Q720) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.120 Mobile Safari/537.36"
        ]
        
        
        if num_agents > len(user_agents):
            num_repeats = num_agents // len(user_agents) + 1
            user_agents *= num_repeats
        
        return user_agents[:num_agents]

    fake_user_agents = generate_fake_user_agents(10)
    for agent in fake_user_agents:
        # print(agent)
        user_agent = agent

    module = ModulesIA("AuthPath")
    resultado = module.render()
    
    if resultado:
        try:
            resultado_dict = json.loads(resultado)
        except json.JSONDecodeError as e:
            return jsonify({"error": "Erro ao decodificar o JSON"}), 400
        
        resultado_dict["User-Agent"] = user_agent

        
        data = {
            "messages": [{"content": pergunta, "role": "user"}],
            "previewToken": None,
            "userId": "6e75da85-5501-4825-ae6b-cd19543d582c",
            "codeModelMode": True,
            "agentMode": {},
            "trendingAgentMode": {},
            "isMicMode": False,
            "isChromeExt": False,
            "githubToken": None
        }

        try:
            headers = {
                "Content-Type": "application/json",
                "User-Agent": user_agent
            }
            
            # Enviar a requisição POST com os dados e cabeçalhos corretos
            chatRequest = requests.post("https://www.blackbox.ai/api/chat", headers=headers, json=data)
            chatRequest.raise_for_status()
            
            formatted_content = chatRequest.content.decode('utf-8')
            response_data = {
                "response": formatted_content
            }
            
            # Redirecionar para a rota '/imc' com os parâmetros de altura e peso
            return jsonify(response_data), 200
            
        except requests.exceptions.RequestException as e:
            module = ModulesIA("Auth")
            module.render()
            return jsonify({"error": f"Erro na requisição: {e}"}), 500
    
    else:
        return jsonify({"error": "Nenhum resultado disponível"}), 404


if __name__ == '__main__':
    app.run(debug=True)
