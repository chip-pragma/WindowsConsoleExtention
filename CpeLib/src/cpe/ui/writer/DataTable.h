#pragma once

#include <string>

#include "WriterBase.h"
#include "cpe/ui/IInitializer.h"

namespace cpe {

template<class TModel>
class DataTable;

template<class TModel>
class DataTableInitializer : public IInitializer {
public:
    explicit DataTableInitializer(DataTable<TModel> &table)
            : IInitializer(static_cast<ICuiElement &>(table)) { }

};

template<class TModel>
class DataTable : public WriterBase<DataTableInitializer<TModel>> {
public:
    ~DataTable() override { }

    void add_column(uint32_t modelIdField, const std::string &caption);

protected:
    void on_write(Buffer &buf) override;

    DataTableInitializer<TModel> make_initializer() override;
};

template<class TModel>
void DataTable<TModel>::add_column(uint32_t modelIdField, const std::string &caption) {
    // TODO Создание столбцов и логика работы с моделями

}

template<class TModel>
void DataTable<TModel>::on_write(Buffer &buf) {
    // TODO Рисование таблицы
}

template<class TModel>
DataTableInitializer<TModel> DataTable<TModel>::make_initializer() {
    return DataTableInitializer<TModel>(*this);
}

}



