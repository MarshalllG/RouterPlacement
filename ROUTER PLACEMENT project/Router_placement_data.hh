//  Router_placement_data.hpp

#ifndef Router_placement_data_hh
#define Router_placement_data_hh

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct point
{
    unsigned row, col; 
};

class RP_Input
{
    friend ostream& operator<<(ostream& os, const RP_Input& in);
public:
    RP_Input (string file_name);
    vector<vector<char> > Cells() const { return cells; }
    char Cell(unsigned r, unsigned c) const {return cells[r][c]; }
    unsigned Rows() const { return rows; }
    unsigned Columns() const { return columns; }
    unsigned Radius() const { return radius; }
    unsigned BackbonePrice() const { return b_price; }
    unsigned RouterPrice() const { return r_price; }
    unsigned Budget() const { return budget; }
    point StartBackbone() const { return start_backbone; }
    bool IsWall (unsigned r, unsigned c) const { return cells[r][c] == '#'; }
    bool IsDot (unsigned r, unsigned c) const { return cells[r][c] == '.'; }
    bool IsLine (unsigned r, unsigned c) const { return cells[r][c] == '-'; }
    // unsigned Target(vector<vector<char> > cells, unsigned rows, unsigned columns) const; // numero
private:
    /* vector<vector<int> > covers; */
    vector<vector<char> > cells;
    unsigned rows, columns; // dimensioni esterne
    unsigned radius; // of router range
    unsigned b_price; // of connecting one single cell to the backbone
    unsigned r_price; // of one wireless router
    unsigned budget; // maximum budget
    point start_backbone; // coordinates
    // unsigned target;
};

class RP_Output
{
    // SOVRACCARICO OPERATORI []
    friend ostream& operator<<(ostream& os, const RP_Output& out);
    // friend istream& operator>>(istream& is, BDS_Output& out);
public:
    RP_Output(const RP_Input& in);
    unsigned RemainingBudget() const { return remaining_budget; }
    unsigned Rows() const { return in.Rows(); }
    unsigned Columns() const { return in.Columns(); }
    // unsigned TotalScore() const { return total_score; }
    // vector<point> Covered() const { return covered; }
    point Backbone(unsigned i) { return backbone[i]; }
    point Router(unsigned i) { return routers[i]; }
    // vector<point> RP_Output::Uncovered(); // numero
    point InsertRouter(unsigned r, unsigned c);
    point InsertBackboneCell(unsigned r, unsigned c);
    vector<vector<char> > OutCells() { return out_cells; }
    // unsigned ComputeScore() const { return 1000*covered.size()+(in.Budget()-(backbone.size()*in.BackbonePrice()+routers.size()*in.RouterPrice())); }
     /* bool Covers(unsigned r, unsigned c) const { return covered[r][c]; } */
    // Cover
    // RemoveRouter
    // RemoveBackbone
    // unsigned Target(vector<vector<char> > cells, unsigned rows, unsigned columns) const; // numero
private:
    // Degree (MURI, ROUTER, Anelli)
    /* vector<vector<int> > covers; */
    const RP_Input& in;
    vector<vector<char> > out_cells;
    vector<point> routers;
    vector<point> backbone;
    // vector<point> uncovered;
    // vector<point> covered;
    unsigned remaining_budget;
    // unsigned total_score;
};


#endif /* Router_placement_data_hh */


