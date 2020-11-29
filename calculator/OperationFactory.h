#pragma once

#include "Operation.h"
#include "InterfaceOperationMaker.h"
#include <memory>

// Realisation of pattern "Abstract Factory" in Calculator.
// OperationFactory -- manage with operation such +,-,=..

/*  Как добавить новую операцию?
 * 1. Необходимо создать класс OperationName и унаследовать его от Operation.
 * 2. Реализовать метод execute -- логику выполнения операции
 * 3. Зарегистрировать операцию в фабрике, используя макрос REGISTER_OPERATION(T, NAME),
 * где T -- OperationName, NAME -- то, как операция будет вызываться в коде
 * */

class OperationFactory {
private:
    // To запретить  create instance of Factory
    OperationFactory() = default;
    ~OperationFactory() = default;
public:
    OperationFactory(const OperationFactory&) = delete;

    // Реализация Singleton фабрики. Фабрика есть в единственном экземпляре
    static OperationFactory& getInstance() {
        static OperationFactory factory;
        return factory;
    }

    // Возвращает соответствующую операцию
    std::unique_ptr<Operation> getOperation(const std::string &operationName) const {
        auto i = makers.find(operationName);
        if (i == makers.end()) {
            throw std::runtime_error("Unknown object type");
        }
        InterfaceOperationMaker* maker = i->second;
        return maker->create();
    }

    // Добавляет makers с ключем key в мапу
    void registerMaker(const std::string& key, InterfaceOperationMaker *maker) {
        if (makers.find(key) != makers.end()) {
            throw std::runtime_error("Multiple makers for given key!");
        }
        makers[key] = maker;
    }

private:
    std::map<std::string, InterfaceOperationMaker*> makers;
};
