import numpy as np

class SimpleNeuralNetwork:
    def __init__(self, input_size):
        # Inicializa os pesos aleatoriamente
        self.weights = np.random.rand(input_size)
        
    def sigmoid(self, x):
        # Função de ativação Sigmoid
        return 1 / (1 + np.exp(-x))
    
    def feedforward(self, input_data):
        # Cálculo da saída da rede neural
        weighted_sum = np.dot(input_data, self.weights)
        return self.sigmoid(weighted_sum)

    def process_crm_data(self, crm_data):
        # Processa dados de CRM
        output = self.feedforward(crm_data)
        return output

# Função principal
if __name__ == "__main__":
    # Dados de exemplo do CRM
    crm_data = np.array([500.0, 100.0, 5.0])  # Exemplo de dados de CRM

    # Cria a rede neural
    neural_network = SimpleNeuralNetwork(input_size=len(crm_data))

    # Processa os dados de CRM
    result = neural_network.process_crm_data(crm_data)
    print(f"Resultado do processamento: {result:.2f}")
