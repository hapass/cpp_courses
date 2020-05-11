#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Image {
    double quality;
    double freshness;
    double rating;
};

struct Params {
    double a;
    double b;
    double c;
};

class Operation {
public:
    Operation(char op, double v): operation(op), value(v) {}

    double Apply(double arg) const {
        if (operation == '+') {
            return arg + value;
        }
        return arg - value;
    }

    void Invert() {
        operation = operation == '+' ? '-' : '+';
    }

private:
    char operation;
    double value;
};

class Function {
public:
    void AddPart(char operation, double value) {
        operations.push_back({operation, value});
    }

    void Invert() {
        for (auto& op : operations) {
            op.Invert();
        }
        reverse(begin(operations), end(operations));
    }

    double Apply(double value) const {
        for (auto& op : operations) {
            value = op.Apply(value);
        }
        return value;
    }

private:
    vector<Operation> operations;
};

Function MakeWeightFunction(const Params& params,
                            const Image& image) {
    Function function;
    function.AddPart('-', image.freshness * params.a + params.b);
    function.AddPart('+', image.rating * params.c);
    return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
    Function function = MakeWeightFunction(params, image);
    return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
    Function function = MakeWeightFunction(params, image);
    function.Invert();
    return function.Apply(weight);
}

int main() {
    Image image = {10, 2, 6};
    Params params = {4, 2, 6};
    cout << ComputeImageWeight(params, image) << endl;
    cout << ComputeQualityByWeight(params, image, 46) << endl;
    return 0;
}