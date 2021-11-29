import type { CustomPaintProps, Vector, AnimatedProps } from "../../processors";
import { materialize } from "../../processors";
import { useDrawing } from "../../nodes/Drawing";

export interface LineProps extends CustomPaintProps {
  p1: Vector;
  p2: Vector;
}

export const Line = (props: AnimatedProps<LineProps>) => {
  const onDraw = useDrawing(
    (ctx) => {
      const { canvas, paint } = ctx;
      const { p1, p2 } = materialize(ctx, props);
      canvas.drawLine(p1.x, p1.y, p2.x, p2.y, paint);
    },
    [props]
  );
  return <skDrawing onDraw={onDraw} {...props} />;
};