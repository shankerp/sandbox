def info(object, spacing=10, collapse=1):
    methodList = [e for e in dir(object) if callable(getattr(object, e))]
    processFunc = collapse and (lambda s: " ".join(s.split())) or (lambda s: s)
    print "\n".join(["%s %s" %
            (method.ljust(spacing),
            processFunc(str(getattr(object, method).__doc__)))
            for method in methodList
            ])
