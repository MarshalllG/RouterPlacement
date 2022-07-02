// RP_Greedy.cc 

#include "RP_Greedy.hh"
#include "Random.hh"
#include <algorithm>
#include <numeric>

using namespace std;

// unsigned ManhattanDistance (point p1, point p2)
// {
//     return abs(p1.row - p2.row) + abs(p1.col - p2.col);
// }

point PlaceRandomizedRouter(const RP_Input& in, RP_Output& out)
{
    unsigned r, c;
    point router;

    do
    {
        r = Random(0, in.Rows()-1);
        c = Random(0, in.Columns()-1);
    } while (in.IsWall(r, c));

    cout << "r, c: " << r << " " << c << endl;
    router = out.InsertRouter(r, c);

    return router;
}

// void ConnectRouterWithBackbone(point router)
// {   
//     point selected_bb_cell, pt;
//     unsigned min_distance = rows+columns;

//     // select the point to connect with the router
//     if (out.backbone.size() == 1)
//         selected_bb_cell = in.StartBackbone();

//     // else
//     // {   
//     //     // search the closest backbone point
//     //     for (unsigned i = 0; i < out.backbone.size(); i++)
//     //     {
//     //         current_distance = ManhattanDistance(router, out.backbone[i]);
//     //         if(current_distance < min_distance)
//     //         {
//     //             min_distance = current_distance;
//     //             selected_bb_cell = out.backbone[i];
//     //         }
//     //     }
//     // }

//     // connect the selected point with router
//     if (router.row > selected_bb_cell.row)
//         for (unsigned i = selected_bb_cell.row; i != router.row; i++)
//         {
//             pt.row = i;
//             pt.col = selected_bb_cell.col;
//             if (!IsInBackbone(pt))
//                 out.backbone.pushback(pt);
//         }
    




            
// }


// point current_router = routers.pop();
//     vector<point> path = minimize_distance(backbone, current_router)
//     unsigned cost = path.size() * in.BackbonePrice() + in.RouterPrice();

//     if (cost <= remaining_budget):
//         for c in path:
//             if d['graph'][c] == Cell.Router:
//                 d['graph'][c] = Cell.ConnectedRouter
//             else:
//                 d['graph'][c] = Cell.Cable

//         return d, True, cost

//     return d, False, cost




void GreedyRP(const RP_Input& in, RP_Output& out)
{ 
    unsigned max_routers = in.Budget() / in.RouterPrice();
    unsigned num_r = 0;
    point router;

    do
    {
        cout << "Max routers: " << max_routers << endl;
        if (num_r < max_routers)
        {
            router = PlaceRandomizedRouter(in, out);
            cout << "Placed router in cell " << router.row << " " << router.col << endl;
            num_r++;
        }
        cout << "numr: " << num_r << endl;
        cout << "Remaining Budget: "  << out.RemainingBudget() << endl;

        // path = ConnectRouterWithBackbone(router, out.backbone);
        // cout << "New Backbone path: " 
        // for (unsigned i = 0; i < path.size(); i++)
        //     cout << path[i].row << " " << path[i].col << ",";
        // cout << endl;
    } while (out.RemainingBudget() > in.RouterPrice());


    cout << out;
}
  
// bool IsInBackbone (point pt)
// {
//     for (unsigned i = 0; i < backbone.size(); i++)
//         if (pt == backbone[i])
//             return 1;

//     return 0;
// }

