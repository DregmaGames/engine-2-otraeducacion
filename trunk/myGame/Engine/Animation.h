#pragma once
#include "myEngine_API.h"
#include <vector>
#include <string>
namespace pGr {

	class Timer;
	class MYENGINE_API Animation{
	public: 
		Animation();
		struct Frame{
						float u1; float v1;
						float u2; float v2;
						float u3; float v3;
						float u4; float v4;

		};
		std::string Name;
		void setName(std::string name){
			Name=name;
		}
		std::string getName(){
			return Name;
		}
		unsigned int currentFrame() const;
		const std::vector<Frame> & frames() const { return m_pkFrames;};
		void addFrame ( float fTextWidth, float fTextHeight,
						float fFramePosX, float fFramePosY,
						float fFrameWidth, float fFrameHeight);
	
	private:
			std::vector<Frame> m_pkFrames;
	public:
		void setLength(float fLength);
		void update(Timer& rkTimer);
	private:
		unsigned int m_CurrentFrame;
		float m_fCurrentTime;
		float m_fLength;
	};
}
