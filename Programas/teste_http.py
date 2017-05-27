import paho.mqtt.client as mqtt
import requests
import urllib2
import json
import ast
message = ' '

#Callback  - chamada quando a conexao eh estabelecida
def on_connect(client, userdata, flags, rc):

    print("Conectado ao broker. Retorno da conexao: "+str(rc))

#Informa que o topico que este subscriber ira "escutar" eh o "Teste" 
    client.subscribe("Edison")

#Callback - chamado quando alguma mensagem eh recebida
def on_message(client, userdata, msg):

	print("Topico: "+msg.topic+" - Mensagem recebida: "+str(msg.payload)) 
	global message
	message = msg.payload
	send_message(message)

def send_message(messages):
	'''	
	from requests_oauthlib import OAuth1
	prat = messages[7]
	api = "http://tcc-industria.azurewebsites.net/api/products/"+prat
	chave = "xEUSUayR_djnAhoHcdygnjlTp_Nus9po6Kq8oGNwgHiTxeksOBjnoiooko9A6jopPrKlSNYUaSk_JNJtiJiS6ocaZomZ9XSMu85oPPa1uYBsS5krgWHtv7Srh8OWvfVCW-MPd69mkKAJ_XCukZVAgjdfRpiFitrkSsVjZywuEAzf95uK7KNuuHsyts-6K-gmeca9IB7ewg_Pr-LDNMrazOtOiLNu6-dxg726KruL75cLQY5LEfHRDKJnpvQqmABRCixd5jwt9sfh_4J7JD7AbHMXPW8g1lwWE9tr276ZDsfb2YPkhNWvIcryXDBo0SYv2khbCzRZgex6GReSTV0qZjQl9ajsne_h8qxZUyMP1gukPWhBwOFNOnkwM0iEkqaWJiYHyouFlHAGOEAgmx0JKak-REg4uvCO8r6ssiOtdHjhev2DJRlydcUrapGKcy6gFgcCmwkgzjZ8uBKXrj6VlbzOGAEPPeLc3wDBhrh20JI"
	headers = {"Authorization" : "Bearer %s" %chave}
	dados = ast.literal_eval(messages)
	

	resposta = requests.get(api, headers = headers)
	print(resposta.text)
	requests.put(api, data=dados, headers=headers)
	resposta = requests.get(api, headers = headers)
	print(resposta.text)
	'''

	id = messages[7]
	api = "http://tcc-industria.azurewebsites.net/api/products/"+id
	dados = ast.literal_eval(messages)
	
	resposta = requests.get(api)
	print(resposta.text)
	requests.put(api, dados)
	resposta = requests.get(api)
	print(resposta.text)
	










#programa principal

client = mqtt.Client()
client.on_connect = on_connect   #configura callback (de quando eh estabelecida a conexao)
client.on_message = on_message    #configura callback (de quando eh recebida uma mensagem)
client.connect("192.168.31.21", 1883, 60)  #tenta se conectar ao broker na porta 1883 (o parametro '60' eh o tempo de keepalive). Nesse caso, $
#Loop infinito aguardando recepcao de mensagens. Esta funcao eh blocante.
client.loop_forever()



