//  Router_placement_data.cpp

#include "Router_placement_data.hh"

RP_Input::RP_Input(string file_name)
{  
    unsigned i, s, n_tasks, t;
    ifstream is(file_name);
    if (!is) 
    {
        cerr << "Cannot open file " <<  file_name << endl;
	    exit(1);
    }

    is >> rows >> columns >> radius
       >> b_price >> r_price >> budget
       >> start_backbone.row >> start_backbone.col;

    cells.resize(columns, vector<char>(columns));

    cout << rows << " " << columns << " " << radius << endl
       << b_price << " " << r_price << " " << budget << endl
       << start_backbone.row << " " << start_backbone.col << endl;
  
    for (unsigned r = 0; r < rows; r++)
    {
        for (unsigned c = 0; c < columns; c++)
        {
            char ch;
            is >> ch;
            cells[r][c] = ch;
        }
    }
}


// unsigned RP_Input::Target(vector<vector<char> > cells, unsigned rows, unsigned columns) const // numero
// {
//     unsigned count = 0;

//     for (unsigned r = 0; r < rows; r++)
//     {
//         for (unsigned c = 0; c < columns; c++)
//         {
//             if (cells[r][c] == '.')
//                 count++;
//         }
//     }
//     return count;
// }


ostream& operator<<(ostream& os, const RP_Input& in)
{
    for (unsigned r = 0; r < in.rows; r++)
    {
        for (unsigned c = 0; c < in.columns; c++)
        {
            os << in.cells[r][c];
        }
        cout << endl;
    }
    return os;
}


RP_Output::RP_Output(const RP_Input& my_in) : in(my_in) // ?????
{
    out_cells = in.Cells(); // for for
    backbone.push_back(in.StartBackbone()); 
    out_cells[in.StartBackbone().row][in.StartBackbone().col] = 'b';
    remaining_budget = in.Budget();
    // total_score = 0;
    // point temp;

    // for (unsigned r = 0; r < in.Rows(); r++)
    // {
    //     for (unsigned c = 0; c < in.Columns(); c++)
    //     {
    //         if (out_cells[r][c] == '.')
    //         {
    //             temp.row = r;
    //             temp.col = c;
    //             uncovered.push_back(temp);
    //         }
    //     }
    // }
}


point RP_Output::InsertRouter(unsigned r, unsigned c)
{
    point router;


    if (!in.IsWall(r, c))
    {
        // update cell
        out_cells[r][c] = 'r';

        router.row = r;
        router.col = c;
        cout << "router.row: " << router.row << " " << "router.col" << router.col << endl;


        routers.push_back(router);

        // // update coverage
        // coverage = out.UpdateCoverage(router);
        // cout << "Updated coverage: " << coverage << endl;

        // update budget
        remaining_budget -= in.RouterPrice();
    }
    // else 
    // {
    //     exit(0);
    //     throw ("err");
    // }

    return router;
}


// point RP_Output::InsertBackboneCell(unsigned r, unsigned c)
// {
//     point bb_cell;
//     bb_cell.row = r;
//     bb_cell.col = c;

//     if (!backbone)
//     // IF Nell'intorno c'è una bbcell
//     backbone.push_back(bb_cell);

//     out.remaining_budget -= in.BackbonePrice();

//     return bb_cell;
// }


// void RP_Output::RemoveRouter(point router)
// {
//     out_cells[router.row][router.col] = in.cells[router.row][router.col];
//     routers.delete()
//     out.remaining_budget += in.RouterPrice();
// }

 
// void RP_Output::RemoveBackboneCell (point bb_cell)
// {
//     backbone.delete()
//     out.remaining_budget += in.BackbonePrice();
// }


ostream& operator<<(ostream& os, const RP_Output& out)
{
    for (unsigned r = 0; r < out.Rows(); r++)
    {
        for (unsigned c = 0; c < out.Columns(); c++)
        {
            os << out.out_cells[r][c];
        }
        cout << endl;
    }
    return os;
}