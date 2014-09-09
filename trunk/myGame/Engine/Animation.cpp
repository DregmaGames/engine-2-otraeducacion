//--------------------------------------------------------------
#include "Animation.h"
#include "pg1_timer.h"
//--------------------------------------------------------------
using namespace pGr;
Animation::Animation(): m_CurrentFrame(0),m_fCurrentTime(0),m_fLength(1.0f){
}
//--------------------------------------------------------------
unsigned int Animation::currentFrame() const {
	return m_CurrentFrame;
}
//--------------------------------------------------------------
void Animation::addFrame(float fTextWidth, float fTextHeight,float fFramePosX, float fFramePosY,float fFrameWidth, float fFrameHeight){
	Frame m_Frame;
	m_Frame.u1 = (fFramePosX/fTextWidth);
	m_Frame.v1 = (fFramePosY/fTextHeight);

	m_Frame.u2 = ((fFramePosX + fFrameWidth)/fTextWidth);
	m_Frame.v2 = (fFramePosY/fTextHeight);
	
	m_Frame.u3 = (fFramePosX/fTextWidth);
	m_Frame.v3 = ((fFramePosY + fFrameHeight)/fTextHeight);

	m_Frame.u4 = (( fFramePosX + fFrameWidth)/ fTextWidth);
	m_Frame.v4 = ((fFramePosY + fFrameHeight)/fTextHeight);
	m_pkFrames.push_back(m_Frame);
}
//--------------------------------------------------------------
void Animation::update (Timer& rkTimer){
	m_fCurrentTime += rkTimer.timeBetweenFrames();
	while(m_fCurrentTime > m_fLength){
		m_fCurrentTime -= m_fLength;
	}
	m_CurrentFrame = static_cast<unsigned int>((m_fCurrentTime /m_fLength )*m_pkFrames.size ());

}
//--------------------------------------------------------------
void Animation::setLength(float fLength){
	m_fLength=fLength;
}