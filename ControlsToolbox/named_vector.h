#ifndef NAMED_VECTOR_H
#define NAMED_VECTOR_H

#include <string>
#include <any>
#include <map>
#include <utility>
#include <vector>
#include <eigen3/Eigen/Dense>

using Eigen::VectorXd;
using Eigen::MatrixXd;

class NamedVector {
    public:
        void Add(std::string name, double value);
        void Add(std::string name, VectorXd value);
        void Add(std::string name, MatrixXd value);

        void Set(std::string name, double value);
        void Set(std::string name, VectorXd value);
        void Set(std::string name, MatrixXd value);
        void Set(VectorXd value);

        template <typename T>
        T Get(std::string name) {return std::any_cast<T>(_values[name].first);};
        VectorXd Get() {return _v;};

        int size() {return _size;};
        int size(bool flag);

    protected:
        VectorXd AsVector();

        VectorXd _v;
        int _size = 0;
        std::vector<std::string> _names;
        std::map<std::string, std::pair<std::any, std::string>> _values;
}; 

NamedVector operator+(NamedVector a, NamedVector b);
NamedVector operator-(NamedVector a, NamedVector b); 
NamedVector operator*(MatrixXd A, NamedVector b); 
NamedVector operator*(int a, NamedVector b);
NamedVector operator*(NamedVector a, int b);
NamedVector operator+(int a, NamedVector b);
NamedVector operator+(NamedVector a, int b);
NamedVector operator*(double a, NamedVector b); 
NamedVector operator*(NamedVector a, double b); 
NamedVector operator+(double a, NamedVector b); 
NamedVector operator+(NamedVector a, double b); 
NamedVector operator+(NamedVector a, VectorXd b);
NamedVector operator+(VectorXd a, NamedVector b);
#endif