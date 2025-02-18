import argparse


def _argparse():
    parser = argparse.ArgumentParser(description="This is description!")
    parser.add_argument('--ip', action='store', required=True,dest='ip', help='The IP of server')
    parser.add_argument('--port', action='store', required=True, dest='port', help='The port of server')
    return parser.parse_args()


def main():
    parser = _argparse()
    print(parser)
    print('IP:', parser.ip)
    print('Port:', parser.port)


if __name__ == '__main__':
    main()
