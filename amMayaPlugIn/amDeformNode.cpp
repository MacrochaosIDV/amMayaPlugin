#include "amDeformNode.h"
#include <maya/MItGeometry.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MMeshIntersector.h>
#include <maya/MPoint.h>


amDeformNode::amDeformNode() {}


amDeformNode::~amDeformNode() {}

void* creator() {
  return new amDeformNode();
}

MStatus amDeformNode::initializePlugin(MObject obj) {
  MStatus status = MS::kInvalidParameter;
  MFnPlugin plugin(obj, "amPlugIn", "0.1.0", "Any");
  status = plugin.registerCommand("amDeformNode", creator);
  return status;
}

MStatus amDeformNode::uninitializePlugin(MObject obj) {
  MStatus status = MS::kInvalidParameter;
  MFnPlugin plugin(obj);
  status = plugin.deregisterCommand("amDeformNode");
  return status;
}

MStatus amDeformNode::deform(MDataBlock& block, 
                             MItGeometry& iter, 
                             const MMatrix& mat, 
                             unsigned int multiIndex) {
  multiIndex;
  mat;
  block;

  MStatus status = MStatus::kUnknownParameter;
  MObject thisNode = this->thisMObject();
  MPlug inPlug(thisNode, input);

  MPointArray verts;
  iter.allPositions(verts);
  unsigned int size = verts.length();
  MPointOnMesh meshPoint;
  
  for (unsigned int i = 0; i < size; ++i) {
    //231
    std::swap(verts[i].x, verts[i].z);
    std::swap(verts[i].y, verts[i].x);
  }

  iter.setAllPositions(verts);
  return status;
}

