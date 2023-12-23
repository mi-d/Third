struct Params {
    int db_connection_timeout;
    bool db_allow_exceptions;
    DBLogLevel db_log_level;
    string_view name_filter;
    int min_age = 0;
    int max_age = 99;
};

vector<Person> LoadPersons(string_view db_name, Params params)
{
    DBConnector connector(params.db_allow_exceptions, params.db_log_level);
    DBHandler db;
    if (db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_name, params.db_connection_timeout);
    }
    else {
        db = connector.Connect(db_name, params.db_connection_timeout);
    }
    if (!params.db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << params.min_age << " and "s << params.max_age << " "s
        << "and Name like '%"s << db.Quote(params.name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({ move(name), age });
    }
    return persons;
}