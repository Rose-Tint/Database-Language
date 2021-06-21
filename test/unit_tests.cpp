#include "unit_tests.h"


void unit_tests()
{
    std::cout << "\033[0;33m~~~~~~~~~~~~ START OF UNIT TESTS ~~~~~~~~~~~~\033[0m\n" << std::endl;

    std::cout << "\033[0;1;36mCell:\033[0m" << std::endl;
    bool cell = check<bool>("Overall", unit_test<Cell>(), true);
    std::cout << std::endl;

    std::cout << "\033[0;1;36mColumn:\033[0m" << std::endl;
    bool column = check<bool>("Overall", cell ? unit_test<Column>() : false, true);
    std::cout << std::endl;

    std::cout << "\033[0;1;36mTable:\033[0m" << std::endl;
    bool table = check<bool>("Overall", column ? unit_test<Table>() : false, true);
    std::cout << std::endl;

    std::cout << "\033[0;33m~~~~~~~~~~~~  END OF UNIT TESTS  ~~~~~~~~~~~~\033[0m" << std::endl;
}


template<class T>
bool check(std::string msg, const T& given, const T& exp)
{
    bool good = (given == exp);
    std::cout << "\t\033[0;1;34m" << msg << "... \033[3"
              << (good ? "2mPass" : "1mFail") << "\033[0m"
              << std::endl;
    return good;
}


template<>
bool unit_test<Cell>()
{
    constexpr unsigned size = 4;

    byte* bytes = new byte[size] { 43, 79, 3, 19 };
    Cell cell(size, bytes, bytes + size);

    bool c_size = check<ushort>("size", cell.size, size);

    byte* exp_byte = bytes;
    byte* cell_byte = cell.value();
    bool c_value = true;
    for (int i = 0; i < cell.size; i++)
        c_value &= check("value" + std::to_string(i), *exp_byte++, *cell_byte++);

    bool c_value_begin = check<byte>("value_begin", *cell.get_value_begin(), *bytes);
    bool c_value_end = check<byte>("value_end", *cell.get_value_end(), *(bytes + size));
    bool test = (c_size && c_value && c_value_begin && c_value_end);

    delete[] bytes;

    return test;
}


template<>
bool unit_test<Column>()
{
    constexpr u8 size = 4;
    constexpr char exp_name[16] = "TestColumn";
    ColumnMetadata cmd =
    {
        {
            exp_name[0]  , exp_name[1]  , exp_name[2]  , exp_name[3]  ,
            exp_name[4]  , exp_name[5]  , exp_name[6]  , exp_name[7]  ,
            exp_name[8]  , exp_name[9]  , exp_name[10] , exp_name[11] ,
            exp_name[12] , exp_name[13] , exp_name[14] , '\0'
        },
        size,
        nullable | unique
    };

    Column col = cmd;

    bool c_name = check<std::string>("name", col.get_name(), exp_name);
    bool c_size = check<u8>("size", col.get_size(), size);
    bool c_props = check<Properties>("properties", col.get_properties(), static_cast<Properties>(nullable|unique));
    bool c_metadata = check<ColumnMetadata>("metadata", col.get_md(), cmd);
    bool test = (c_name && c_size && c_props && c_metadata);

    return test;
}


// TODO: FINISH
template<>
bool unit_test<Table>()
{
    constexpr char exp_name[16] = "TestTable";
    constexpr u8 col_c = 3;
    constexpr u16 obj_c = 0;
    constexpr u8 col_sizes[col_c] = { 3, 4, 2 };
    constexpr char col_names[3][16] = { "TestCol1", "TestCol2", "TestCol3" };

    TableMetadata tmd = 
    {
        {
            exp_name[0]  , exp_name[1]  , exp_name[2]  , exp_name[3]  ,
            exp_name[4]  , exp_name[5]  , exp_name[6]  , exp_name[7]  ,
            exp_name[8]  , exp_name[9]  , exp_name[10] , exp_name[11] ,
            exp_name[12] , exp_name[13] , exp_name[14] , '\0'
        },
        col_c,
        obj_c
    };

    std::vector<Column> cols;
    for (int i = 0; i < col_c; i++)
    {
        ColumnMetadata cmd =
        {
            {
                col_names[i][0]  , col_names[i][1]  , col_names[i][2]  , col_names[i][3]  ,
                col_names[i][4]  , col_names[i][5]  , col_names[i][6]  , col_names[i][7]  ,
                col_names[i][8]  , col_names[i][9]  , col_names[i][10] , col_names[i][11] ,
                col_names[i][12] , col_names[i][13] , col_names[i][14] , '\0'
            },
            col_sizes[i],
            nullable | unique
        };
        cols.emplace_back(cmd);
    }

    Table tbl(tmd, cols);
    Object obj = tbl.create_object();
    
    tbl.insert(obj);

    bool name = check<std::string>("name", tbl.get_name(), exp_name);
    bool insert = check<Object>("insert", tbl.get_objects()[0], obj);

    return name && insert;
}
