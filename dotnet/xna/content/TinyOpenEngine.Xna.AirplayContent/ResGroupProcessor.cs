using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content.Pipeline;
using Microsoft.Xna.Framework.Content.Pipeline.Graphics;
using Microsoft.Xna.Framework.Content.Pipeline.Processors;
using TinyOpenEngine.AirplayContent;

namespace TinyOpenEngine.Xna.AirplayContent
{
	/// <summary>
	/// This class will be instantiated by the XNA Framework Content Pipeline
	/// to apply custom processing to content data, converting an object of
	/// type TInput to TOutput. The input and output types may be the same if
	/// the processor wishes to alter data without changing its type.
	///
	/// This should be part of a Content Pipeline Extension Library project.
	///
	/// TODO: change the ContentProcessor attribute to specify the correct
	/// display name for this processor.
	/// </summary>
	[ContentProcessor(DisplayName = "TinyOpenEngine.Xna.AirplayContent.ResGroupProcessor")]
	public class ResGroupProcessor : ContentProcessor<CIwResGroup, CIwResGroup>
	{
		public override CIwResGroup Process(CIwResGroup input, ContentProcessorContext context)
		{
			// TODO: process the input object, and return the modified data.
			throw new NotImplementedException();
		}
	}
}