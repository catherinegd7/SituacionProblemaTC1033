#pragma once
#include <string>
#include <stdexcept>

enum class Category {
    Supermercado,
    Restaurante,
    Hogar,
    Electronica,
    Transporte,
    Entretenimiento,
    Servicios, 
    Salud
};

inline Category stringToCategory(const std::string& str) {
    if (str == "Supermercado") return Category::Supermercado;
    if (str == "Restaurante") return Category::Restaurante;
    if (str == "Hogar") return Category::Hogar;
    if (str == "Electronica") return Category::Electronica;
    if (str == "Transporte") return Category::Transporte;
    if (str == "Entretenimiento") return Category::Entretenimiento;
    if (str == "Servicios") return Category::Servicios;
    if (str == "Salud") return Category::Salud;
    throw std::invalid_argument("Categoria desconocida: " + str);
}
inline std::string categoryToString(Category c) {
    switch (c) {
        case Category::Supermercado:    return "Supermercado";
        case Category::Restaurante:     return "Restaurante";
        case Category::Hogar:           return "Hogar";
        case Category::Electronica:     return "Electronica";
        case Category::Transporte:      return "Transporte";
        case Category::Entretenimiento: return "Entretenimiento";
        case Category::Servicios:       return "Servicios";
        case Category::Salud:           return "Salud";
    }
    return "Desconocido";
}
