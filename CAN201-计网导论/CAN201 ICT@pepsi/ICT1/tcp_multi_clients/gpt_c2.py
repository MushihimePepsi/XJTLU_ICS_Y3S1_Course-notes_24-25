import socket
import argparse
import json


class GameClient:
    def __init__(self, server_ip, server_port):
        self.server_ip = server_ip
        self.server_port = server_port
        self.client_socket = None
        self.name = None
    
    def connect(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((self.server_ip, self.server_port))
        print(f"Connected to server at {self.server_ip}:{self.server_port}")
    
    def play_game(self):
        try:
            while True:
                # Receive message from server
                message = self.receive_message()
                
                if message["type"] == "name_request":
                    # Server requesting name
                    self.name = input("Enter your name: ")
                    self.send_message({"type": "name", "name": self.name})
                
                elif message["type"] == "wait_message":
                    # Waiting for other players
                    print(message["message"])
                
                elif message["type"] == "game_start":
                    # Game is starting
                    print(message["message"])
                
                elif message["type"] == "your_turn":
                    # It's this client's turn
                    print(message["message"])
                    while True:
                        try:
                            guess = int(input("Enter your guess: "))
                            if 1 <= guess <= 100:
                                break
                            print("Please enter a number between 1 and 100.")
                        except ValueError:
                            print("Please enter a valid number.")
                    
                    self.send_message({"type": "guess", "guess": guess})
                
                elif message["type"] == "guess_result":
                    # Result of someone's guess
                    print(message["message"])
                
                elif message["type"] == "game_over":
                    # Game has ended
                    if message["winner"] == self.name:
                        print("Congratulations! You guessed the number!")
                    else:
                        print(f"{message['winner']} guessed the number and won the game!")
                    break
        
        except Exception as e:
            print(f"Error: {e}")
    
    def send_message(self, message):
        message_json = json.dumps(message)
        self.client_socket.send(message_json.encode() + b'\n')
    
    def receive_message(self):
        data = self.client_socket.recv(1024).decode().strip()
        return json.loads(data)
    
    def cleanup(self):
        if self.client_socket:
            self.client_socket.close()


def main():
    parser = argparse.ArgumentParser(description='Number Guessing Game Client')
    parser.add_argument('--ip', required=True, help='Server IP address')
    parser.add_argument('--port', type=int, required=True, help='Server port')
    args = parser.parse_args()
    
    client = GameClient(args.ip, args.port)
    try:
        client.connect()
        client.play_game()
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client.cleanup()


if __name__ == "__main__":
    main()