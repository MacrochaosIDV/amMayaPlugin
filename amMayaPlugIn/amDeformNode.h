#pragma once
#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>
#include <maya/MPxDeformerNode.h>


class amDeformNode : public MPxGeometryFilter
{
public:
  amDeformNode();
  ~amDeformNode();

  static MStatus
  initializePlugin(MObject obj);

  static MStatus
  uninitializePlugin(MObject obj);

  MStatus deform(MDataBlock& block, 
                 MItGeometry& iter, 
                 const MMatrix& mat, 
                 unsigned int multiIndex) override;


  static	MObject	deformingMesh;
};



static void*
creator();
