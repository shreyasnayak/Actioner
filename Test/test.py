import json
import socket

# Server address and port
server_address = '127.0.0.1'
server_port = 12345

# Create a TCP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to the server
    client_socket.connect((server_address, server_port))
    print('Connected to server.')

    # Create a JSON message
    message = {
        'name': 'John Doe',
        'age': 30,
        'city': 'Example City'
    }
    json_message = json.dumps(message).encode('utf-8')

    # Send the JSON message to the server
    client_socket.sendall(json_message)
    print('JSON message sent.')

    # Receive the response from the server
    response = client_socket.recv(1024)
    print('Response from server:', response.decode('utf-8'))

finally:
    # Close the socket
    client_socket.close()