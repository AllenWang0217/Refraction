#pragma once
#include "json/json.h"
#include <string>

using namespace std;

void printInvoices(Json::Value& root);
void printPlays(Json::Value& root);
bool jsonReader(string& path, Json::Value& root);
