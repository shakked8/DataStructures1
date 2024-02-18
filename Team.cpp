#include "Team.h"

bool Team::isContestantInTeam(Contestant *contestant) {
    return (m_tree1.isNodeInTree(contestant->getContestantId()) ||
            m_tree2.isNodeInTree(contestant->getContestantId()) ||
            m_tree3.isNodeInTree(contestant->getContestantId()));
}

//void Team::insertTree1(Contestant *contestant) {
//    Node<Contestant>* nodebyId = new Node<Contestant>(contestant->getContestantId(), contestant);
//    Node<Contestant>* nodebyStrength = new Node<Contestant>(contestant->getStrength(), contestant);
//    m_tree1.insert(nodebyId);
//    m_tree1Strength.insert(nodebyStrength);
//}
//void Team::insertTree2(Contestant *contestant) {
//    Node<Contestant>* nodebyId = new Node<Contestant>(contestant->getContestantId(), contestant);
//    Node<Contestant>* nodebyStrength = new Node<Contestant>(contestant->getStrength(), contestant);
//    m_tree2.insert(nodebyId);
//    m_tree2Strength.insert(nodebyStrength);
//}
//void Team::insertTree3(Contestant *contestant) {
//    Node<Contestant>* nodebyId = new Node<Contestant>(contestant->getContestantId(), contestant);
//    Node<Contestant>* nodebyStrength = new Node<Contestant>(contestant->getStrength(), contestant);
//    m_tree3.insert(nodebyId);
//    m_tree3Strength.insert(nodebyStrength);
//}


void Team::moveToRightTree(AVLTree<Contestant> *t1, AVLTree<Contestant> *t2) {
    Node<Contestant>* node = t1->maxValueNode(); // find node to move
    deleteNodeFronStrength(node); // out of tree by strength
    t1->deleteNode(node); //out of tree by id
    t2->insert(node);
    insertNodeToStrength(node->strengthNode);
}
//
//Node<Contestant> *Team::getNodeByStrength(Node<Contestant>* node) {
//    if(m_tree1.isNodeInTree(node->m_object->getContestantId())){
//        return m_tree1Strength.findNode(node->m_object->getContestantId());
//    }if(m_tree2.isNodeInTree(node->m_object->getContestantId())){
//        return m_tree2Strength.findNode(node->m_object->getContestantId());
//    }if(m_tree3.isNodeInTree(node->m_object->getContestantId())){
//        return m_tree3Strength.findNode(node->m_object->getContestantId());
//    }
//}
//Node<Contestant> *Team::getNodeById(Node<Contestant>* node) {
//    if(m_tree1Strength.isNodeInTree(node->m_object->getContestantId())){
//        return m_tree1.findNode(node->m_object->getContestantId());
//    }if(m_tree2Strength.isNodeInTree(node->m_object->getContestantId())){
//        return m_tree2.findNode(node->m_object->getContestantId());
//    }if(m_tree3Strength.isNodeInTree(node->m_object->getContestantId())){
//        return m_tree3.findNode(node->m_object->getContestantId());
//    }
//}


//void removeNodeFromTeam(Node<Contestant> *node){
//    deleteNodeFronStrength(node); // out of tree by strength
//
//}
void Team::deleteNodeFronStrength(Node<Contestant> *node) {
    Node<Contestant>* nodeByStrenth = node->strengthNode;
    if(m_tree1.isNodeInTree(node->m_object->getContestantId())){
        m_tree1Strength.deleteNode(nodeByStrenth);
    }if(m_tree2.isNodeInTree(node->m_object->getContestantId())){
        m_tree2Strength.deleteNode(nodeByStrenth);
    }if(m_tree3.isNodeInTree(node->m_object->getContestantId())){
        m_tree3Strength.deleteNode(nodeByStrenth);
    }
}

//insert the matching node (the one by strength) to the matching tree
void Team::insertNodeToStrength(Node<Contestant> *node) {
    Node<Contestant>* nodeByStrenth = node->strengthNode;
    if(m_tree1.isNodeInTree(node->m_object->getContestantId())){
        m_tree1Strength.deleteNode(nodeByStrenth);
    }if(m_tree2.isNodeInTree(node->m_object->getContestantId())){
        m_tree2Strength.deleteNode(nodeByStrenth);
    }if(m_tree3.isNodeInTree(node->m_object->getContestantId())){
        m_tree3Strength.deleteNode(nodeByStrenth);
    }
}
AVLTree<Contestant>* Team::getMinTree() {
    if (tree1Size <= tree2Size && tree1Size <= tree3Size) {
        return &m_tree1;
    } else if (tree2Size <= tree1Size && tree2Size <= tree3Size) {
        return &m_tree2;
    } else {
        return &m_tree3;
    }
}
