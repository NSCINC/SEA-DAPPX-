import subprocess
import json
from flask import Flask, request, jsonify

app = Flask(__name__)

# Função para chamar o programa C via subprocess para validação de token NSC
def validate_nsc_token(token):
    result = subprocess.run(['./nsc_token_validator', token], capture_output=True, text=True)
    return result.stdout.strip() == "valid"

# Função para rodar o script Lua (contrato de investimento)
def run_lua_contract(script, function, *args):
    command = f"lua {script} {function} " + " ".join(map(str, args))
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

@app.route('/add-plan', methods=['POST'])
def add_plan():
    data = request.json
    token = data.get('token')
    plan_name = data.get('plan_name')
    initial_investment = data.get('initial_investment')
    crm_data = data.get('crm_data')

    # Validar o token NSC
    if not validate_nsc_token(token):
        return jsonify({"error": "Token NSC inválido"}), 400

    # Executa o contrato Lua
    result = run_lua_contract('investment_contract.lua', 'add_plan', plan_name, initial_investment)
    return jsonify({"message": result})

@app.route('/invest', methods=['POST'])
def invest():
    data = request.json
    plan_name = data.get('plan_name')
    amount = data.get('amount')
    investor_address = data.get('investor_address')

    # Executa o contrato Lua
    result = run_lua_contract('investment_contract.lua', 'invest', plan_name, amount, investor_address)
    return jsonify({"message": result})

# Inicia o servidor Flask na porta 8080
if __name__ == '__main__':
    app.run(port=8080)
