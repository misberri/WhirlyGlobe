//
//  StickersTestCase.swift
//  AutoTester
//
//  Created by jmnavarro on 3/11/15.
//  Copyright © 2015 mousebird consulting. All rights reserved.
//

import UIKit

class StickersTestCase: MaplyTestCase {

	override init() {
		super.init()
		
		self.name = "Stickers"
		self.captureDelay = 4
		self.implementations = [.globe, .map]
	}

	func addStickers (_ arrayComp: NSArray , baseViewC: MaplyBaseViewController) {
		let startImage = UIImage(named: "Smiley_Face_Avatar_by_PixelTwist")
		var stickers = [MaplySticker]()
		for object in arrayComp {
			let sticker = MaplySticker()
			let center = (object as! MaplyVectorObject).center()
			sticker.ll = center
			sticker.ur = MaplyCoordinate(x: center.x + 0.1, y: center.y+0.1)
			sticker.image = startImage
			stickers.append(sticker)
		}
		baseViewC.addStickers(stickers, desc: [kMaplyFade: (1.0)])
	}
	
	override func setUpWithGlobe(_ globeVC: WhirlyGlobeViewController) {
		let baseLayer = VectorsTestCase()
		baseLayer.setUpWithGlobe(globeVC)
		addStickers(baseLayer.compList, baseViewC: globeVC)
	}
	
	override func setUpWithMap(_ mapVC: MaplyViewController) {
		let baseLayer = VectorsTestCase()
		baseLayer.setUpWithMap(mapVC)
		addStickers(baseLayer.compList, baseViewC: mapVC)
	}
}
