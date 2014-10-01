#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofMesh mesh;
    
    // Control group. This should have no errors.
    mesh.load("hand151.ply");
    cout << "Should be 0 :" << check_triangle_intersections(mesh) << endl;
    
    // Test for various errors.
    
    mesh.load("faulty2Triangles.ply");
    cout << "Should Be 1 :" << check_triangle_intersections(mesh) << endl;
    
    mesh.load("hand-2014-151v-Lmanuallyfaulted.ply");
    cout << "Should Be 1 :" << check_triangle_intersections(mesh) << endl;

    mesh.load("hand-2014-151v-L-faulty2.ply");
    cout << "Should Be 1 :" << check_triangle_intersections(mesh) << endl;
        
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    
}

// Enable the user to drag ply files into the window.
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
