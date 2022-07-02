// RP_Greedy.hh
#ifndef _RP_GREEDY_HH_
#define _RP_GREEDY_HH_
#include "Router_placement_data.hh"

point PlaceRandomizedRouter(const RP_Input& in);
void GreedyRP(const RP_Input& in, RP_Output& out);


// class RP_GreedySolver
// {
// public:
//     ConnectRouterWithBackbone()
//     PlaceRandomizedRouter()
// private:
//     const RP_Input& in;
//     unsigned max_routers = in.Budget() / in.RouterPrice();
// }

#endif
