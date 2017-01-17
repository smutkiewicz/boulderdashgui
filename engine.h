#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include<stdbool.h>
#include"header.h"

bool WszystkieDiamenty(struct stangry*stanplanszy);
void ZjedzDiament(struct stangry*stanplanszy);
void PrzesunDiament(int i, int j, int kpionowy, struct stangry*stanplanszy);
void PrzesunKamien(int i, int j, int kpionowy, int kpoziomy, struct stangry*stanplanszy);
void WykonajOstatniRuch(struct wsppostaci*danerf, struct stangry*stanplanszy);
void WykonajRuch(int i, int j, struct wsppostaci*danerf, struct stangry*stanplanszy);
bool SprawdzCzyPoleJestPuste(int i, int j, struct stangry*stanplanszy);
void Ruch(int i, int j, int kpionowy, int kpoziomy, struct wsppostaci*danerf, struct stangry*stanplanszy);
void Graj(int Znak, struct wsppostaci*danerf, struct stangry*stanplanszy);
int PobierzZnak();
void StabilizujKolumny(int j, struct stangry*stanplanszy);
void Stabilizuj(struct stangry*stanplanszy);
void PobierzPlansze(struct wsppostaci*, struct stangry*, char*);

#endif //ENGINE_H_INCLUDED
