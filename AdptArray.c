/*
Code by Ilan Meir Souffir : 342615648
With the help of the Tirgul ADT from the C course, the exam of C (moad a, 2023).
*/

#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"
#include "book.h"

typedef struct AdptArray_ {
    int ArrSize;
    PElement* pElemArr;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc){
    PAdptArray pArr = (PAdptArray) malloc(sizeof(AdptArray));
    if (pArr == NULL) 
        return NULL;
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->copyFunc = copyFunc;
    pArr->delFunc = delFunc;
    pArr->printFunc = printFunc;
    return pArr;
}

void DeleteAdptArray(PAdptArray pArr){
    if (pArr == NULL) 
        return;
    for (int i = 0  ; i < pArr->ArrSize; ++i) {
        if (pArr->pElemArr[i] != NULL) {
            pArr->delFunc(pArr->pElemArr[i]);
        }else{
            free(pArr->pElemArr[i]);
        }
    }
    free(pArr->pElemArr);
    free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem) {
    if (pArr == NULL || idx < 0)  
        return FAIL;
    if (idx >= pArr->ArrSize){
        pArr->pElemArr = (PElement*) realloc(pArr->pElemArr, (idx+1)*sizeof(pNewElem));
        if (pArr->pElemArr == NULL)
            return FAIL;
        for (int i = pArr->ArrSize; i < idx + 1; i++) {
            pArr->pElemArr[i] = NULL;
        }
        pArr->ArrSize = idx + 1; 
    }
    if (pArr->pElemArr[idx] != NULL) 
        pArr->delFunc(pArr->pElemArr[idx]);
    pArr->pElemArr[idx] = pArr->copyFunc(pNewElem);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    if (pArr == NULL || pArr->ArrSize <= idx ||pArr->pElemArr[idx] == NULL || idx < 0) {
        return NULL;
    }
    return  pArr->copyFunc(pArr->pElemArr[idx]);
}

int GetAdptArraySize(PAdptArray pArr ) {
    if (pArr == NULL)
        return -1;
    return  pArr->ArrSize;
}

void PrintDB(PAdptArray pArr){
    if (pArr == NULL)
        return;
    for (int i = 0; i < pArr->ArrSize; i++) {
        if (pArr->pElemArr[i] != NULL)
            pArr->printFunc(pArr->pElemArr[i]);    
    }
}
