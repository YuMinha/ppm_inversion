#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

void printMenu();
int getUserChoice();
int selectImage(const std::vector<std::string>& imageList);
void ClearConsole(int sec);