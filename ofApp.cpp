#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetColor(255);
	ofSetLineWidth(1.5);
	ofNoFill();
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 1);
	this->triangles = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int log = 20;
	int span = 600;

	for (int x = -span; x <= span; x += span) {

		for (int y = -span; y <= span; y += span) {

			ofPushMatrix();
			ofTranslate(x, y, 0);

			float noise_seed_x = ofRandom(1000);
			float noise_seed_y = ofRandom(1000);
			float noise_seed_z = ofRandom(1000);
			for (auto& triangle : this->triangles) {

				glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;

				ofBeginShape();
				for (int i = 0; i < log; i++) {

					auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + i) * 0.003), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
					auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + i) * 0.003), 0, 1, -PI, PI), glm::vec3(0, 1, 0));
					auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_z, (ofGetFrameNum() + i) * 0.003), 0, 1, -PI, PI), glm::vec3(0, 0, 1));

					glm::vec3 location = glm::vec4(avg, 0) * rotation_z * rotation_y * rotation_x;
					ofVertex(location);

					if (i == log - 1) {

						ofFill();
						ofDrawSphere(location, 5);
						ofNoFill();
					}
				}
				ofEndShape(false);
			}

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}