#include "amDeformNode.h"
#include <maya/MItGeometry.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MMeshIntersector.h>
#include <maya/MPoint.h>
#include <maya/MTypeId.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnMeshData.h>
#include <maya/MFnNumericAttribute.h>

#include <maya/MIOStream.h>

#include <maya/MPxGeometryFilter.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MMeshIntersector.h>

//#include <maya/MThreadUtils.h>
//#include <tbb/tbb.h>

amDeformNode::amDeformNode() {}


amDeformNode::~amDeformNode() {}

void* creator() {
  return new amDeformNode();
}

MStatus initialize() {
  // local attribute initialization
  MStatus status;
  MFnTypedAttribute mAttr;
  amDeformNode::deformingMesh = mAttr.create("deformingMesh", 
                                             "dm", 
                                             MFnMeshData::kMesh);
  mAttr.setStorable(true);

  //  deformation attributes
  //status = addAttribute(deformingMesh);
  //MCheckStatus(status, "ERROR in addAttribute(deformingMesh)\n");
  //status = attributeAffects(deformingMesh, outputGeom);
  //MCheckStatus(status, "ERROR in attributeAffects(deformingMesh)\n");

  //return status;
  return MStatus::kSuccess;
}

MStatus amDeformNode::initializePlugin(MObject obj) {
  MStatus status = MS::kInvalidParameter;
  MFnPlugin plugin(obj, "amPlugIn", "0.1.0", "Any");
  status = plugin.registerNode("amDeformNode", 
                               type_ID, 
                               creator, 
                               initialize, 
                               MPxNode::Type::kDeformerNode);
  return status;
}

MStatus amDeformNode::uninitializePlugin(MObject obj) {
  MStatus status = MS::kInvalidParameter;
  MFnPlugin plugin(obj);
  status = plugin.deregisterNode(type_ID);
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

