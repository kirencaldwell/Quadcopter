#include "named_vector.h"
#include <iostream>

int NamedVector::size(bool flag) {
    if (flag) {
        return (int)_names.size();
    }
    else {
        return _size;
    }
}

void NamedVector::Add(std::string name, double value) {
    _names.push_back(name);
    std::pair<std::any, std::string> in(value, "double");
    _values[name] = in;
    _size++;
    _v.resize(_size);
    _v = AsVector();
}
void NamedVector::Add(std::string name, VectorXd value) {
    _names.push_back(name);
    std::pair<std::any, std::string> in(value, "vector");
    _values[name] = in;
    _size += value.size();
    _v.resize(_size);
    _v = AsVector();
}
void NamedVector::Add(std::string name, MatrixXd value) {
    _names.push_back(name);
    std::pair<std::any, std::string> in(value, "matrix");
    _values[name] = in;
    _size += value.size();
    _v.resize(_size);
    _v = AsVector();
}

void NamedVector::Set(std::string name, double value) {
    if (_values.count(name) == 1) {
        _values[name].first = value;
    }
    _v.resize(_size);
    _v = AsVector();
}
void NamedVector::Set(std::string name, VectorXd value) {
    if (_values.count(name) == 1) {
        VectorXd v = std::any_cast<VectorXd>(_values[name].first);
        if (v.size() == value.size()) {
            _values[name].first = value;
        }
        else {
            std::cout << "size mismatch of " << name << std::endl;
        }
        _v.resize(_size);
        _v = AsVector();
    }
}
void NamedVector::Set(std::string name, MatrixXd value) {
    if (_values.count(name) == 1) {
        MatrixXd m = std::any_cast<MatrixXd>(_values[name].first);
        if (m.size() == value.size()) {
            _values[name].first = value;
        }
        else {
            std::cout << "size mismatch of " << name << std::endl;
        }
        _v.resize(_size);
        _v = AsVector();
    }
}
void NamedVector::Set(VectorXd value) {
    VectorXd current = _v;
    if (current.size() == value.size()) {
        int ctr = 0;
        for (int i = 0; i < (int)_names.size(); i++) {
            std::string name_i = _names[i];
            if (_values[name_i].second == "double") {
                _values[name_i].first = (double)value(ctr);
                ctr++;
            }
            else if (_values[name_i].second == "vector") {
                VectorXd v = std::any_cast<VectorXd>(_values[name_i].first);
                for (int j = 0; j < v.size(); j++) {
                    v(j) = value(ctr);
                    ctr++;
                }
                _values[name_i].first = v;
            }
            else if (_values[name_i].second == "matrix") {
                MatrixXd m = std::any_cast<MatrixXd>(_values[name_i].first);
                VectorXd v = m.reshaped(m.size(),1);
                for (int j = 0; j < v.size(); j++) {
                    v(j) = value(ctr);
                    ctr++;
                }
                m = v.reshaped(m.rows(), m.cols());
                _values[name_i].first = m;
            }
        }
        _v = value;
    }
    else {
        std::cout << "size mismatch when trying to set" << std::endl;
    }
}


VectorXd NamedVector::AsVector() {
    VectorXd out(_size);
    int ctr = 0;
    for (int i = 0; i < (int)_names.size(); i++) {
        std::string name_i = _names[i];
        if (_values[name_i].second == "double") {
            out(ctr) = std::any_cast<double>(_values[name_i].first);
            ctr++;
        }
        else if (_values[name_i].second == "vector") {
            VectorXd v = std::any_cast<VectorXd>(_values[name_i].first);
            for (int j = 0; j < v.size(); j++) {
                out(ctr) = v(j);
                ctr++;
            }
        }
        else if (_values[name_i].second == "matrix") {
            MatrixXd m = std::any_cast<MatrixXd>(_values[name_i].first);
            VectorXd v = m.reshaped(m.size(),1);
            for (int j = 0; j < v.size(); j++) {
                out(ctr) = v(j);
                ctr++;
            }
        }
    }
    return out;
}

NamedVector operator+(NamedVector a, NamedVector b) {
    NamedVector out = a;
    out.Set(a.Get() + b.Get());
    return out;
}
NamedVector operator-(NamedVector a, NamedVector b) {
    NamedVector out = a;
    out.Set(a.Get() - b.Get());
    return out;
}

NamedVector operator*(MatrixXd A, NamedVector b) {
    NamedVector out = b;
    out.Set(A*b.Get());
    return out;
}

NamedVector operator*(int a, NamedVector b) {
    NamedVector out = b;
    out.Set(a*b.Get());
    return out;
}
NamedVector operator*(NamedVector a, int b) {
    NamedVector out = a;
    out.Set(b*a.Get());
    return out;
}
NamedVector operator+(int a, NamedVector b) {
    NamedVector out = b;
    out.Set(a*VectorXd::Ones(b.Get().size()) + b.Get());
    return out;
}
NamedVector operator+(NamedVector a, int b) {
    NamedVector out = a;
    out.Set(b*VectorXd::Ones(a.Get().size()) + a.Get());
    return out;
}
NamedVector operator*(double a, NamedVector b) {
    NamedVector out = b;
    out.Set(a*b.Get());
    return out;
}
NamedVector operator*(NamedVector a, double b) {
    NamedVector out = a;
    out.Set(b*a.Get());
    return out;
}
NamedVector operator+(double a, NamedVector b) {
    NamedVector out = b;
    out.Set(a*VectorXd::Ones(b.Get().size()) + b.Get());
    return out;
}
NamedVector operator+(NamedVector a, double b) {
    NamedVector out = a;
    out.Set(b*VectorXd::Ones(a.Get().size()) + a.Get());
    return out;
}
NamedVector operator+(NamedVector a, VectorXd b) {
    NamedVector out = a;
    out.Set(a.Get() + b);
    return out;
}
NamedVector operator+(VectorXd a, NamedVector b) {
    NamedVector out = b;
    out.Set(b.Get() + a);
    return out;
}