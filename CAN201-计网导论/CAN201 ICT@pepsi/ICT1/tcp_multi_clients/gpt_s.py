import socket
import argparse
import random
import json


class GameServer:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.server_socket = None
        self.clients = []  # List of (socket, address, name) tuples
        self.target_number = None
        self.current_player_index = 0
    
    def start(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)
        print(f"Server started on {self.host}:{self.port}")
    
    def accept_clients(self, num_clients=2):
        while len(self.clients) < num_clients:
            client_socket, address = self.server_socket.accept()
            print(f"Client connected: {address}")
            
            # Ask for client's name
            self.send_message(client_socket, {"type": "name_request"})
            name_data = self.receive_message(client_socket)
            client_name = name_data["name"]
            print(f"Received name: {client_name}")
            
            self.clients.append((client_socket, address, client_name))
            
            # Notify client to wait for other players
            self.send_message(client_socket, {
                "type": "wait_message",
                "message": "Waiting for other players..."
            })
    
    def start_game(self):
        print("All clients are ready. Starting the game.")
        self.target_number = random.randint(1, 100)
        print(f"Random number generated: {self.target_number}")
        
        # Notify all clients that game has started
        self.broadcast_message({
            "type": "game_start",
            "message": "Game started!"
        })
        
        self.game_loop()
    
    def game_loop(self):
        game_over = False
        
        while not game_over:
            current_client = self.clients[self.current_player_index]
            current_socket = current_client[0]
            current_name = current_client[2]
            
            print(f"Prompting {current_name} to guess.")
            
            # Notify current player it's their turn
            self.send_message(current_socket, {
                "type": "your_turn",
                "message": "Your turn to guess."
            })
            
            # Get guess from current player
            guess_data = self.receive_message(current_socket)
            guess = int(guess_data["guess"])
            print(f"Received guess {guess} from {current_name}.")
            
            if guess == self.target_number:
                # Winner found
                winner_message = f"{current_name} wins!"
                print(winner_message)
                self.broadcast_message({
                    "type": "game_over",
                    "winner": current_name,
                    "message": winner_message
                })
                game_over = True
            else:
                # Wrong guess
                hint = "too high" if guess > self.target_number else "too low"
                broadcast_message = f"{current_name} guessed {guess}. The guess is {hint}."
                print(broadcast_message)
                self.broadcast_message({
                    "type": "guess_result",
                    "message": broadcast_message
                })
                
                # Move to next player
                self.current_player_index = (self.current_player_index + 1) % len(self.clients)
    
    def broadcast_message(self, message):
        for client_socket, _, _ in self.clients:
            self.send_message(client_socket, message)
    
    def send_message(self, client_socket, message):
        message_json = json.dumps(message)
        client_socket.send(message_json.encode() + b'\n')
    
    def receive_message(self, client_socket):
        data = client_socket.recv(1024).decode().strip()
        return json.loads(data)
    
    def cleanup(self):
        for client_socket, _, _ in self.clients:
            client_socket.close()
        self.server_socket.close()


def main():
    parser = argparse.ArgumentParser(description='Number Guessing Game Server')
    parser.add_argument('--ip', required=True, help='Server IP address')
    parser.add_argument('--port', type=int, required=True, help='Server port')
    args = parser.parse_args()
    
    server = GameServer(args.ip, args.port)
    try:
        server.start()
        server.accept_clients(2)  # Wait for 2 clients
        server.start_game()
    except Exception as e:
        print(f"Error: {e}")
    finally:
        server.cleanup()


if __name__ == "__main__":
    main()