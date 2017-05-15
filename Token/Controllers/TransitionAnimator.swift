import Foundation
import UIKit

class PopAnimator: NSObject, UIViewControllerAnimatedTransitioning {
    
    let duration = 0.6
    var presenting = true
    var originFrame = CGRect.zero
    
    var dismissCompletion: (()->Void)?
    
    func transitionDuration(using transitionContext: UIViewControllerContextTransitioning?) -> TimeInterval {
        return duration
    }
    
    func animateTransition(using transitionContext: UIViewControllerContextTransitioning) {
        let containerView = transitionContext.containerView
        
        let toView = transitionContext.view(forKey: .to)!
        
        let targetView = presenting ? toView : transitionContext.view(forKey: .from)!
        
        let initialFrame = presenting ? originFrame : targetView.frame
        let finalFrame = presenting ? targetView.frame : originFrame
        
        let xScaleFactor = presenting ?
            
            initialFrame.width / finalFrame.width :
            finalFrame.width / initialFrame.width
        
        let yScaleFactor = presenting ?
            
            initialFrame.height / finalFrame.height :
            finalFrame.height / initialFrame.height
        
        let scaleTransform = CGAffineTransform(scaleX: xScaleFactor, y: yScaleFactor)
        
        if presenting {
            targetView.transform = scaleTransform
            targetView.center = CGPoint(
                x: initialFrame.midX,
                y: initialFrame.midY)
            targetView.clipsToBounds = true
        }
        
        containerView.addSubview(toView)
        containerView.bringSubview(toFront: targetView)
        
        UIView.animate(withDuration: duration, delay:0.0, usingSpringWithDamping: 0.7,
                       initialSpringVelocity: 0.0,
                       animations: {
                        targetView.transform = self.presenting ?
                            CGAffineTransform.identity : scaleTransform
                        targetView.center = CGPoint(x: finalFrame.midX,
                                                    y: finalFrame.midY)
        },
                       completion:{_ in
                        if !self.presenting {
                            self.dismissCompletion?()
                        }
                        transitionContext.completeTransition(true)
        }
        )
    }
    
}
