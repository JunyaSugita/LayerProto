#include "Frame.h"

void Frame::Initialize()
{
	for (int i = 0; i < this->GetLayerFrameHeight(); i++)
	{
		for (int j = 0; j < this->GetLayerFrameWidth(); j++)
		{
			//this->layersInTheFrame[i][j].clear();
		}
	}
}
