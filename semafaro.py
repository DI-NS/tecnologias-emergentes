import serial
import pymongo
from datetime import datetime

# Configuração do MongoDB
client = pymongo.MongoClient("mongodb://localhost:27017/")
db = client["semaforo_iot"]
collection = db["solicitacoes_travessia"]

# Configuração da porta serial
porta = serial.Serial("COM3", 9600)  # Substituir COM3 pela porta correta

print("Aguardando dados do Arduino...")

while True:
    if porta.in_waiting > 0:
        mensagem = porta.readline().decode("utf-8").strip()
        print(f"Mensagem recebida: {mensagem}")

        if "Solicitacao de travessia registrada" in mensagem:
            # Criar registro no banco de dados
            registro = {
                "data_hora": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                "status": "Solicitação de travessia registrada"
            }
            collection.insert_one(registro)
            print("Solicitação registrada no MongoDB:", registro)
