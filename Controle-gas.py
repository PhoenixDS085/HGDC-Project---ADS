import serial
import time
import tkinter as tk
from tkinter import messagebox

PORTA_BLUETOOTH = 'COM4'
BAUD_RATE = 9600

# Tenta conectar ao Bluetooth
try:
    bluetooth = serial.Serial(COM5, 9600)
    time.sleep(2)
except Exception as e:
    messagebox.showerror("Erro", f"Erro ao conectar: {e}")
    exit()

# Envia comando via Bluetooth
def enviar_comando(cmd):
    try:
        bluetooth.write(cmd.encode())
    except:
        messagebox.showerror("Erro", "Erro ao enviar comando")

# Criando interface
janela = tk.Tk()
janela.title("Controle do Carrinho Arduino")

# Tamanho e organização
janela.geometry("300x300")
janela.resizable(False, False)

# Botões
btn_frente = tk.Button(janela, text="Frente", command=lambda: enviar_comando('W'), width=10, height=2)
btn_tras   = tk.Button(janela, text="Trás", command=lambda: enviar_comando('S'), width=10, height=2)
btn_esq    = tk.Button(janela, text="Esquerda", command=lambda: enviar_comando('A'), width=10, height=2)
btn_dir    = tk.Button(janela, text="Direita", command=lambda: enviar_comando('D'), width=10, height=2)
btn_parar  = tk.Button(janela, text="Parar", command=lambda: enviar_comando('X'), width=22, height=2, bg="red", fg="white")

# Layout
btn_frente.pack(pady=5)
btn_esq.pack(pady=5)
btn_dir.pack(pady=5)
btn_tras.pack(pady=5)
btn_parar.pack(pady=10)

# Fechar conexão ao sair
def sair():
    bluetooth.close()
    janela.destroy()

janela.protocol("WM_DELETE_WINDOW", sair)

 # Inicia interface
janela.mainloop()