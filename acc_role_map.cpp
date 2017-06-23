#include "acc_role_map.h"
AccRoleMap::AccRoleMap() {};
AccRoleMap::~AccRoleMap() {};

string AccRoleMap::GetAccID()
{
    return acc_id;
}

string AccRoleMap::GetRoleID()
{
    return role_id;
}

void AccRoleMap::ReadMapInfo(string matched_line)
{
    vector<string> info;
    ReadLineInfo(matched_line, info);

    acc_id = info[0];
    role_id = info[1];
    //cout << acc_id << " " << role_id << endl;
}
