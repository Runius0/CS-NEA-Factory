#include "Recipe.h"


int numRecipes[256];
Recipe* recipeRegistry[256][256];

ItemStack* Recipe::getResult() {
	return result;
}
int Recipe::getTime() {
	return craftingTicks;
}
ItemStack** Recipe::getIngredients() {
	return ingredients;
}

Recipe::Recipe(ItemStack** _ingredients, ItemStack* _result, int _craftingTicks) {
	for (int i = 0; i < 8; i++) {
		ingredients[i] = _ingredients[i];
		if (_ingredients[i] == NULL) {
			break;
		}
	}
	result = _result;
	craftingTicks = _craftingTicks;

};

void Recipe::drawRecipeInfo(SDL_Renderer* renderer, float x, float y) {

    char* recipeText[20];
    int ingredientNumber = 1;

    char itemAmountString[5];
    int amount = result->getAmount();
    int amountDigits = SDL_log10(amount) + 1;
    for (int i = 0; i < amountDigits; i++) {
        itemAmountString[amountDigits - i - 1] = (amount % 10) + 48;
        amount /= 10;
    }

    // insane C string concatenation fuckery wizard magic (100% consistent and blazingly fast)
    recipeText[0] = new char[40];
    memcpy(recipeText[0], itemAmountString, amountDigits);
    memcpy(recipeText[0] + amountDigits, "x ", 2);
    memcpy(recipeText[0] + amountDigits + 2, result->type->name, 32);

    recipeText[1] = new char[40];
    memcpy(recipeText[1], "", 1);

    recipeText[2] = new char[40];
    memcpy(recipeText[2], "INGREDIENTS", 12);
    int ingredientNum = 0;

    while (ingredients[ingredientNum] != NULL) {
        recipeText[ingredientNum + 3] = new char[40];

        amount = ingredients[ingredientNum]->getAmount();
        amountDigits = SDL_log10(amount) + 1;
        for (int i = 0; i < amountDigits; i++) {
            itemAmountString[amountDigits - i - 1] = (amount % 10) + 48;
            amount /= 10;
        }

        memcpy(recipeText[ingredientNum + 3], itemAmountString, amountDigits);
        memcpy(recipeText[ingredientNum + 3] + amountDigits, "x ", 2);
        memcpy(recipeText[ingredientNum + 3] + amountDigits + 2, ingredients[ingredientNum]->type->name, 32);

        ingredientNum++;
    }

    recipeText[ingredientNum + 3] = new char[40];
    memcpy(recipeText[ingredientNum + 3], "", 1);



    recipeText[ingredientNum + 4] = new char[40];
    memcpy(recipeText[ingredientNum + 4], "TIME ", 5);

    amount = craftingTicks / TPS;
    amountDigits = SDL_log10(amount) + 1;
    if (amount == 0) {
        amountDigits = 1; // this will cause an error anywhere else in the code but this is the only place it's likely to occur, so only fix here for now.
    }
    for (int i = 0; i < amountDigits; i++) {
        itemAmountString[amountDigits - i - 1] = (amount % 10) + 48;
        amount /= 10;
    }

    memcpy(recipeText[ingredientNum + 4] + 5, itemAmountString, amountDigits);

    int decimalAmount = (craftingTicks % TPS) * 5;
    itemAmountString[0] = '.'; // add decimal point hardcoded as we know the length of the decimal
    for (int i = 0; i < 2; i++) {
        itemAmountString[2 - i] = (decimalAmount % 10) + 48;
        decimalAmount /= 10;
    }
    memcpy(recipeText[ingredientNum + 4] + amountDigits + 5, itemAmountString, 3);
    memcpy(recipeText[ingredientNum + 4] + amountDigits + 8, "", 1);


    drawTextStrings(renderer, x, y, (char**)recipeText, ingredientNum + 5, 40);

    // clear up memory here because otherwise it's the biggest memory leak in the entire program
    for (int i = 0; i < ingredientNum + 5; i++) {
        delete[] recipeText[i];
    }
}


void registerRecipe(RecipeType category, Recipe* toAdd) {
	int ID = numRecipes[category];
	recipeRegistry[category][ID] = toAdd;
	numRecipes[category]++;
};