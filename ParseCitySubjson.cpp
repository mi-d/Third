#include <vector>
#include <string>

using namespace std;

struct City {
    std::string name;
    std::string iso_code;
    std::string phone_code;
    std::string country_name;
    std::string counrty_iso_code;
    std::string country_time_zone;
    std::vector<Language> languages;
};

struct CountryParams {
    std::string name;
    std::string iso_code;
    std::string phone_code;
    std::string time_zone;
    std::vector<Language> languages;
};

// Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
void ParseCitySubjson(vector<City>& cities, const Json& json, const CountryParams params) {
    for (const auto& city_json : json.AsList()) {
        const auto& city_obj = city_json.AsObject();
        cities.push_back({ .name = city_obj["name"s].AsString(), 
                           .iso_code = city_obj["iso_code"s].AsString(),
                           .phone_code = params.phone_code + city_obj["phone_code"s].AsString(),
                           .country_name = params.name,
                           .counrty_iso_code = params.iso_code,
                           .country_time_zone = params.time_zone,
                           .languages = params.languages });
    }
}

// ParseCitySubjson вызывается только из функции ParseCountryJson следующим образом:
void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString(),
            });
        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        ParseCitySubjson(cities, country_obj["cities"s], 
            { .country_name = country.name,
              .counrty_iso_code = country.iso_code,
              .phone_code = country.phone_code,
              .time_zone = country.time_zone,
              .languages = country.languages
            });
    }
}