#include "./TreeMerger.h"
//#include <stdexcept>
//
//vector<CommonFieldTree> TreeMerger::ReturnMergedTrees(vector<CommonFieldTree> Trees) {
//    vector<CommonFieldTree> CombinedTrees;
//    for (const auto& Tree : Trees) {
//        bool found = false;
//        for (auto& CombinedTree : CombinedTrees) {
//            if (Tree.UsedPieceIndex == CombinedTree.UsedPieceIndex) {
//                CombinedTree = RecurseMergeTree(CombinedTree, Tree);
//                found = true;
//            }
//        }
//        if (!found) {
//            CombinedTrees.push_back(Tree);
//        }
//    }
//    return CombinedTrees;
//}
//
//std::pair<string, vector<CommonFieldTree>> TreeMerger::MergeNodes(std::pair<string, vector<CommonFieldTree>> NodeA, std::pair<string, vector<CommonFieldTree>> NodeB) {
//    if (NodeA.first != NodeB.first) throw std::invalid_argument("Nodes provided should not be combined, they do not have the same key string.");
//    vector<CommonFieldTree> AllTrees = NodeA.second;
//    AllTrees.insert(AllTrees.end(), NodeB.second.begin(), NodeB.second.end());
//    return { NodeA.first, ReturnMergedTrees(AllTrees)};
//}
//
//CommonFieldTree TreeMerger::RecurseMergeTree(CommonFieldTree TreeA, CommonFieldTree TreeB) {
//    //if the UsedPieceIndex are the same, that means each sub-section of sequences can be merged.
//    //if the pieceIndex of a tree is the same inside the sequence sub-section, recurse.
//    //if leaves are merged, combine the set of solutions.
//
//    //sanity check
//    if ((TreeA.UsedPieceIndex != TreeB.UsedPieceIndex) or (TreeA.SolvePercent != TreeB.SolvePercent)) throw std::invalid_argument("Trees provided should not be combined, they do not have the same pieceIndex/SolvePercentage.");
//    int newUsedPieceIndex = TreeA.UsedPieceIndex;
//    double newSolvePercent = TreeA.SolvePercent;
//
//    vector<std::pair<string, vector<CommonFieldTree>>> CombinedNodes;
//    if (TreeA.childNodes[0].second.size() == 0) { //only leaf node has empty vector<CommonFieldTree>
//        vector<std::pair<string, vector<CommonFieldTree>>> AllChildNodes = TreeA.childNodes;
//        AllChildNodes.insert(AllChildNodes.end(), TreeB.childNodes.begin(), TreeB.childNodes.end());
//        for (const auto& node : AllChildNodes) {
//            bool found = false;
//            for (auto& CombinedNode : CombinedNodes) {
//                if (node.first == CombinedNode.first) {
//                    CombinedNode = MergeNodes(CombinedNode, node);
//                    found = true;
//                }
//            }
//            if (!found) {
//                CombinedNodes.push_back(node);
//            }
//        }
//    }
//    return { newUsedPieceIndex, newSolvePercent, CombinedNodes };
//}
//
