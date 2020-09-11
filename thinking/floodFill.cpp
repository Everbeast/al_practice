//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/flood-fill/
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
    fill(image,sr, sc, image[sr][sc], newColor);
    return image;
}

void fill(vector<vector<int>>& image, int x, int y, int ogColor, int newColor){
    if(!inArea(image, x, y)) return;
    if(image[x][y] != ogColor) return;
    if(image[x][y] == -1) return;

    image[x][y] = -1; //visited;
    fill(image, x - 1, y, ogColor, newColor);
    fill(image, x, y - 1, ogColor, newColor);
    fill(image, x + 1, y, ogColor, newColor);
    fill(image, x, y + 1, ogColor, newColor);
    image[x][y] = newColor;

}

bool inArea(vector<vector<int>>& image, int x, int y){
    return x >=0 && x < image.size() && y >= 0 && y < image[0].size();
}

