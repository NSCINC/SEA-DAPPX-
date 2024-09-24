const express = require('express');
const { exec } = require('child_process');
const app = express();
app.use(express.json());

// Função para executar IA e CRM usando C
const runAIProcessing = (token, crmData, callback) => {
    const command = `./process_data ${token} ${crmData.join(' ')}`;
    exec(command, (error, stdout, stderr) => {
        if (error) {
            callback(error, null);
        } else {
            callback(null, stdout);
        }
    });
};

// Rota para autenticar e processar
app.post('/process-crm', (req, res) => {
    const { token, crmData } = req.body;

    runAIProcessing(token, crmData, (error, result) => {
        if (error) {
            res.status(500).send('Erro ao processar dados');
        } else {
            res.send(`Resultado IA: ${result}`);
        }
    });
});

app.listen(8080, () => {
    console.log('Servidor rodando na porta 8080');
});
