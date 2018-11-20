(function ($) {
  /**
   * Create any svg element.
   *
   * @param type
   *  SVG node type: svg, line, rect etc.
   * @param params
   *  Object with svg node's parameters.
   * @returns {HTMLElement | SVGAElement | SVGCircleElement |
   *     SVGClipPathElement | SVGComponentTransferFunctionElement |
   *     SVGDefsElement | SVGDescElement | SVGEllipseElement |
   *     SVGFEBlendElement | SVGFEColorMatrixElement |
   *     SVGFEComponentTransferElement | SVGFECompositeElement |
   *     SVGFEConvolveMatrixElement | SVGFEDiffuseLightingElement |
   *     SVGFEDisplacementMapElement | SVGFEDistantLightElement |
   *     SVGFEFloodElement | SVGFEFuncAElement | SVGFEFuncBElement |
   *     SVGFEFuncGElement | SVGFEFuncRElement | SVGFEGaussianBlurElement |
   *     SVGFEImageElement | SVGFEMergeElement | SVGFEMergeNodeElement |
   *     SVGFEMorphologyElement | SVGFEOffsetElement | SVGFEPointLightElement |
   *     SVGFESpecularLightingElement | SVGFESpotLightElement |
   *     SVGFETileElement | SVGFETurbulenceElement | SVGFilterElement |
   *     SVGForeignObjectElement | SVGGElement | SVGImageElement |
   *     SVGGradientElement | SVGLineElement | SVGLinearGradientElement |
   *     SVGMarkerElement | SVGMaskElement | SVGPathElement |
   *     SVGMetadataElement | SVGPatternElement | SVGPolygonElement |
   *     SVGPolylineElement | SVGRadialGradientElement | SVGRectElement |
   *     SVGSVGElement | SVGScriptElement | SVGStopElement | SVGStyleElement |
   *     SVGSwitchElement | SVGSymbolElement | SVGTSpanElement |
   *     SVGTextContentElement | SVGTextElement | SVGTextPathElement |
   *     SVGTextPositioningElement | SVGTitleElement | SVGUseElement |
   *     SVGViewElement | SVGElement | Element}
   */
  function getNode(type, params) {
    type = document.createElementNS('http://www.w3.org/2000/svg', type);

    for (var param in params) {
      type.setAttributeNS(null, param, params[param]);
    }

    return type;
  }

  /**
   * Create line for attach to svg element.
   *
   * @param params
   *  Object with line node's parameters.
   * @returns {SVGElement}
   */
  function createLine(params) {
    return getNode('line', params);
  }

  Drupal.behaviors.getItemInfo = {
    attach: function (context) {
      // Load block with artifact info using ajax delivery callback.
      $(context).on('click', '.item-clickable', function () {
        // Fetch node id of clicked target.
        const nid = $(this).data('nid');

        // Load block.
        $('#block-artifact-info-content').load('/node/get/ajax/' + nid);
      })
      // After block loaded creates lines between images in block.
          .ajaxComplete(function (event, xhr, settings) {
            if (window.location.pathname === '/artifacts') {
              const $block = $('#block-artifact-info-content');
              const targetArticle = $block.find('.target-node article');
              const topArticles = $block.find('.used-for-items article');
              const bottomArticles = $block.find('.require-items article');

              // Create svg between rows in block.
              const svgTop = getNode('svg', {width: '100%', height: 50});
              const svgBottom = getNode('svg', {width: '100%', height: 50});

              // Get count of every row artifacts in block.
              const topCount = $(topArticles).length;
              const bottomCount = $(bottomArticles).length;

              // Get main artifact's position placed on center of block.
              // Margin = 16px + 5px border.
              const targetCoordX = $(targetArticle).position().left + 21;

              if (topCount > 0) {
                // Attach svg between top and center rows.
                $('.used-for-items').after(svgTop);

                // For every article in row calculate coordinates and create
                // lines for svg.
                $(topArticles).each(function () {
                  // We need only left coordinate of every image in the row.
                  const coordX = $(this).position().left + 16;
                  // Create line node.
                  const line = createLine({
                    x1: coordX,
                    y1: 0,
                    x2: targetCoordX,
                    y2: 50,
                    stroke: '#777'
                  });
                  // Attach line node to svg.
                  svgTop.append(line);
                });
              }
              // All comments the same for this logic. See above.
              if (bottomCount > 0) {
                $('.require-items').before(svgBottom);

                $(bottomArticles).each(function () {
                  const coordX = $(this).position().left + 16;
                  const line = createLine({
                    x1: coordX,
                    y1: 50,
                    x2: targetCoordX,
                    y2: 0,
                    stroke: '#777'
                  });
                  svgBottom.append(line);
                });
              }
            }
          });
    }
  };
})(jQuery);