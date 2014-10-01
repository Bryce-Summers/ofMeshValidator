//
//  MeshValidator.h
//  ofApp
//
//  Created by Tube on 10/1/14.
//
//

#ifndef __ofApp__MeshValidator__
#define __ofApp__MeshValidator__

#include <stdio.h>

#include "ofMesh.h"

// Returns true iff the mesh contains two index defined traingles that intersect.
bool check_triangle_intersections(ofMesh &mesh);


int Intersecting(ofVec3f &p0, ofVec3f &p1, ofVec3f &t0, ofVec3f &t1, ofVec3f &t2);


bool point_triangle_intersection(ofVec3f &t1, ofVec3f &t2, ofVec3f &t3, ofVec3f &point);

void BarycentricCoords(const ofVec3f & vTriVtx1,
                       const ofVec3f & vTriVtx2,
                       const ofVec3f & vTriVtx3,
                       const ofVec3f & vVertex,
                       float & fBary1, float & fBary2, float & fBary3 );


#endif /* defined(__ofApp__MeshValidator__) */
