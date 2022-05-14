#pragma once

#include "ByteStream.hpp"

/**
 * @note: It is a extremely simplified RNN
 *        which cannot handle even 2-dimension data & float.
 *        Good luck.
 */

enum RNNType { Naive, LSTM };

class RNNCellBase {
protected:
    static inline int relu(int x) {
        return x > 0 ? x : 0;
    }

    static inline int tanh(int x) {
        return (int) tanhf((float) x);
    }

public:
    /** @param: x - the input
     *  @param: h - the prev hidden state
     *  @return: the output & the new hidden state
     */
    virtual int forward(int x, int h) = 0;
};

class NaiveRNNCell : public RNNCellBase {
    int input_w;
    int hidden_w;
    int bias;

public:
    NaiveRNNCell(int _input_w, int _hidden_w, int _bias)
        : input_w(_input_w), hidden_w(_hidden_w), bias(_bias) {
    }

    virtual int forward(int x, int h) override {
#ifdef SIMPLE_ACTIVATE
        return relu(input_w * x + hidden_w * h + bias);
#else
        return tanh(input_w * x + hidden_w * h + bias);
#endif
    }
};

class LSTMCell : public RNNCellBase {
    // TODO: Maybe new members and new constructor
    // Remember to modify the constructor of 'RNN' after rewrite this class
public:
    // TODO: Maybe fill in it?
    virtual int forward(int x, int h) override {
        return x;
    }
};

class RNN {
    RNNCellBase *cell;
    int hidden;
    int init_hidden;

    RNN(int _input_w,
        int _hidden_w,
        int _bias,
        int _hidden = 0,
        RNNType type = RNNType::Naive)
        : hidden(_hidden), init_hidden(_hidden) {
        if (type == RNNType::Naive)
            cell = new NaiveRNNCell(_input_w, _hidden_w, _bias);
        else if (type == RNNType::LSTM)
            cell = new LSTMCell();
        else
            assert(false);
    }

public:
    static RNN *from_byte_stream(ByteStream *bs) {
    }

    const std::vector<int> &forward(const std::vector<int> &input_seq) {
        std::vector<int> res;
        for (int x : input_seq) {
            hidden = cell->forward(x, hidden);
            res.push_back(hidden);
        }
        hidden = init_hidden;  // Clear
        return res;
    }

    ~RNN() {
        delete cell;
    }
};