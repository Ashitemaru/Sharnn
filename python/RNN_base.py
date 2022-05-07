import torch

def main():
    rnn = torch.nn.RNN(10, 20, 2)
    input = torch.randn(5, 3, 10)
    h0 = torch.randn(2, 3, 20)
    output, hn = rnn(input, h0)

    print(output)
    print(hn)

if __name__ == "__main__":
    main()
